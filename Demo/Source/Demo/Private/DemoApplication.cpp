#include "Demo\DemoApplication.h"

// Library includes

// External includes
#include "GL/glew.h"
#include "SDL.h"

// Engine includes
#include "Data/PooledString.h"
#include "Common/Engine.h"
#include "Events/MouseButtonEvent.h"
#include "Graphics/Color.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"
#include "Math/MathUtil.h"
#include "Math/Mat44.h"
#include "Math/Transform.h"
#include "Math/Vec3D.h"
#include "Util/FileUtils.h"

// Temporary data format declarations
struct MeshVertexDataFormat
{
    engine::math::Vec3D         position;
    engine::graphics::Color     color;
    float                       padding;
};

constexpr uint16_t g_vertex_count = 8;
constexpr uint16_t g_index_count = 36;

engine::math::Mat44 g_model_matrix;
engine::math::Mat44 g_camera_matrix;
engine::math::Mat44 g_projection_matrix;

engine::math::Transform g_model_transform;
engine::math::Transform g_camera_transform;

bool DemoApplication::Init()
{
    if (engine::application::SDLApplication::Init() == false)
    {
        return false;
    }

    mouse_event_receipt_ = engine::input::InputProcessor::Get()->AddListener(
        std::bind(&DemoApplication::OnMouseEvent, this, std::placeholders::_1)
    );
    ASSERT(mouse_event_receipt_.IsValid());//, "Couldn't add a mouse event listener!"

    keyboard_event_receipt_ = engine::input::InputProcessor::Get()->AddListener(
        std::bind(&DemoApplication::OnKeyboardEvent, this, std::placeholders::_1)
    );
    ASSERT(keyboard_event_receipt_.IsValid());//, "Couldn't add a keyboard event listener!"

    InitGraphicsProgram();
    InitMesh();
    InitTransforms();

    return true;
}

void DemoApplication::Update()
{
    SDLApplication::Update();

    static constexpr float camera_speed = 0.1f;
    const engine::math::Vec3D camera_delta(
        (is_left_pressed_ ? camera_speed : (is_right_pressed_ ? -camera_speed : 0.0f)),
        (is_up_pressed_ ? -camera_speed : (is_down_pressed_ ? camera_speed : 0.0f)),
        (is_forward_pressed_ ? camera_speed : (is_back_pressed_ ? -camera_speed : 0.0f))
    );
    g_camera_transform.SetPosition(g_camera_transform.GetPosition() + camera_delta);

    engine::math::GetObjectToWorldTransform(g_camera_transform, g_camera_matrix);
    engine::math::GetObjectToWorldTransform(g_model_transform, g_model_matrix);
}

void DemoApplication::Render()
{
    SDLApplication::Render();

    graphics_program_.Bind();

    graphics_program_.SetUniform("g_camera_view", g_projection_matrix);
    graphics_program_.SetUniform("g_world_camera", g_camera_matrix);
    graphics_program_.SetUniform("g_model_world", g_model_matrix);

    glBindVertexArray(vertex_array_id_);
    ASSERT(glGetError() == GL_NO_ERROR);

    glDrawElements(GL_TRIANGLES, g_index_count, GL_UNSIGNED_INT, 0);
    ASSERT(glGetError() == GL_NO_ERROR);
}

void DemoApplication::OnMouseEvent(const engine::events::MouseButtonEvent& i_event)
{
    const SDL_MouseButtonEvent& sdl_event = i_event.GetSDLEvent();
    LOG("%s TYPE:%s BUTTON:%d X:%d Y:%d",
        __FUNCTION__, (sdl_event.type == SDL_MOUSEBUTTONDOWN ? "DOWN" : "UP"), sdl_event.button, sdl_event.x, sdl_event.y);
}

void DemoApplication::OnKeyboardEvent(const engine::events::KeyboardEvent& i_event)
{
    const SDL_KeyboardEvent& sdl_event = i_event.GetSDLEvent();
    is_forward_pressed_ = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_w;
    is_back_pressed_    = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_s;
    is_left_pressed_    = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_a;
    is_right_pressed_   = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_d;
    is_up_pressed_      = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_e;
    is_down_pressed_    = sdl_event.state == SDL_PRESSED && sdl_event.keysym.sym == SDLK_q;
    //LOG("%s KEY:%d", __FUNCTION__, sdl_event.keysym.sym);
}

void DemoApplication::InitGraphicsProgram()
{
    static const engine::data::PooledString vertex_shader_file_path("Content\\Shaders\\mesh_vertex_shader.glsl");
    static const engine::data::PooledString fragment_shader_file_path("Content\\Shaders\\mesh_fragment_shader.glsl");

    if (graphics_program_.Initialize(vertex_shader_file_path, fragment_shader_file_path) == false)
    {
        LOG_ERROR("Failed to initialize the graphics program. Check above for details.");
        engine::RequestShutdown();
    }
}

void DemoApplication::InitMesh()
{
    // Create a vertex array object and make it active
    {
        constexpr GLsizei array_count = 1;
        glGenVertexArrays(array_count, &vertex_array_id_);
        // TODO: Add error handling here
        glBindVertexArray(vertex_array_id_);
        // TODO: Add error handling here
    }

    // Create a vertex buffer object and make it active
    {
        constexpr GLsizei buffer_count = 1;
        glGenBuffers(buffer_count, &vertex_buffer_id_);
        // TODO: Add error handling here
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
        // TODO: Add error handling here
    }

    // Assign data to the vertex buffer
    {
        constexpr float half_size = 1.0f;
        const MeshVertexDataFormat vertex_data[g_vertex_count] = {
            { engine::math::Vec3D(-half_size, -half_size, half_size),   engine::graphics::Color::RED },
            { engine::math::Vec3D(half_size, -half_size, half_size),    engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, half_size, half_size),     engine::graphics::Color::BLUE },
            { engine::math::Vec3D(-half_size, half_size, half_size),    engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, -half_size, -half_size),   engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(-half_size, -half_size, -half_size),  engine::graphics::Color::RED },
            { engine::math::Vec3D(-half_size, half_size, -half_size),   engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, half_size, -half_size),    engine::graphics::Color::BLUE },
        };

        constexpr size_t buffer_size = g_vertex_count * sizeof(MeshVertexDataFormat);
        // TODO: Add buffer size bounds checks
        glBufferData(GL_ARRAY_BUFFER, buffer_size, vertex_data, GL_STATIC_DRAW);
        // Vertex data can be freed at this point
    }

    // Create an index buffer and make it active
    {
        constexpr GLsizei buffer_count = 1;
        glGenBuffers(buffer_count, &index_buffer_id_);
        ASSERT(glGetError() == GL_NO_ERROR);
        // TODO: Add error handling here
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
        ASSERT(glGetError() == GL_NO_ERROR);
        // TODO: Add error handling here
    }

    // Assign data to the index buffer
    {
        const uint32_t indices[g_index_count] = { 
            0, 1, 2, 0, 2, 3,       // front
            4, 5, 6, 4, 6, 7,       // back
            5, 0, 3, 5, 3, 6,       // left
            1, 4, 7, 1, 7, 2,       // right
            3, 2, 7, 3, 7, 6,       // top
            5, 4, 1, 5, 1, 0        // bottom
        };

        constexpr size_t buffer_size = g_index_count * sizeof(uint32_t);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, indices, GL_STATIC_DRAW);
        ASSERT(glGetError() == GL_NO_ERROR);
    }

    // Initialize vertex attribute
    {
        constexpr GLsizei stride = static_cast<GLsizei>(sizeof(MeshVertexDataFormat));

        // Position
        {
            constexpr GLuint    vertex_position_location = 0;
            constexpr GLuint    element_count = 3;
            glVertexAttribPointer(vertex_position_location,
                element_count,
                GL_FLOAT,
                GL_FALSE,
                stride, reinterpret_cast<void*>(offsetof(MeshVertexDataFormat, position))
            );
            // TODO: Add error handling here
            glEnableVertexAttribArray(vertex_position_location);
            // TODO: Add error handling here
        }

        // Color
        {
            constexpr GLuint    vertex_color_location = 1;
            constexpr GLuint    element_count = 4;
            glVertexAttribPointer(vertex_color_location,
                element_count,
                GL_FLOAT,
                GL_TRUE,
                stride, reinterpret_cast<void*>(offsetof(MeshVertexDataFormat, color))
            );
            // TODO: Add error handling here
            glEnableVertexAttribArray(vertex_color_location);
            // TODO: Add error handling here
        }
    }
}

void DemoApplication::InitTransforms()
{
    const engine::math::Vec3D camera_position = g_camera_transform.GetPosition() + 
                                                engine::math::Vec3D(0.0f, 0.0f, -10.0f);
    g_camera_transform.SetPosition(camera_position);
    engine::math::GetObjectToWorldTransform(g_camera_transform, g_camera_matrix);

    engine::math::GetObjectToWorldTransform(g_model_transform, g_model_matrix);

    static constexpr float fov = float(engine::math::PI) * 0.5f;
    static constexpr float aspect_ratio = 1.0f;
    static constexpr float near_plane = 0.1f;
    static constexpr float far_plane = 1000.0f;
    g_projection_matrix = engine::math::Mat44::GetPerspectiveProjection(fov, aspect_ratio, near_plane, far_plane);
}
