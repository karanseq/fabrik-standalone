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
#include "Math/Vec3D.h"
#include "Util/FileUtils.h"

// Temporary data format declarations
struct MeshVertexDataFormat
{
    engine::math::Vec3D         position;
    engine::graphics::Color     color;
};
constexpr uint16_t vertex_count = 3;

bool DemoApplication::Init()
{
    if (engine::application::SDLApplication::Init() == false)
    {
        return false;
    }

    mouse_event_receipt_ = engine::input::InputProcessor::Get()->AddListener(
        std::bind(&DemoApplication::OnMouseEvent, this, std::placeholders::_1)
        );
    if (mouse_event_receipt_.IsValid() == false)
    {
        LOG_ERROR("Couldn't add a mouse event listener!");
        return false;
    }

    InitGraphicsProgram();
    InitMesh();

    return true;
}

void DemoApplication::Render()
{
    SDLApplication::Render();

    graphics_program_.Bind();

    glBindVertexArray(vertex_array_id_);
    ASSERT(glGetError() == GL_NO_ERROR);

    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void DemoApplication::OnMouseEvent(const engine::events::MouseButtonEvent& i_event)
{
    const SDL_MouseButtonEvent& sdl_event = i_event.GetSDLEvent();
    LOG("%s TYPE:%s BUTTON:%d X:%d Y:%d",
        __FUNCTION__, (sdl_event.type == SDL_MOUSEBUTTONDOWN ? "DOWN" : "UP"), sdl_event.button, sdl_event.x, sdl_event.y);
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
        const MeshVertexDataFormat vertex_data[vertex_count] = {
            { engine::math::Vec3D(0.0f, 0.0f, 0.0f),    engine::graphics::Color::RED },
            { engine::math::Vec3D(0.25f, 0.0f, 0.0f),   engine::graphics::Color::GREEN },
            { engine::math::Vec3D(0.125f, 0.25f, 0.0f), engine::graphics::Color::BLUE }
        };

        constexpr size_t buffer_size = vertex_count * sizeof(MeshVertexDataFormat);
        // TODO: Add buffer size bounds checks
        glBufferData(GL_ARRAY_BUFFER, buffer_size, vertex_data, GL_STATIC_DRAW);
        // Vertex data can be freed at this point
    }

    // Create an index buffer and make it active
    {
        constexpr GLsizei buffer_count = 1;
        glGenBuffers(buffer_count, &index_buffer_id_);
        // TODO: Add error handling here
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
        // TODO: Add error handling here
    }

    // Assign data to the index buffer
    {
        constexpr uint16_t index_count = 3;
        const uint16_t indices[index_count] = { 0, 1, 2 };

        constexpr size_t buffer_size = index_count * sizeof(uint16_t);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, indices, GL_STATIC_DRAW);
    }

    // Initialize vertex attribute
    {
        constexpr GLsizei stride = static_cast<GLsizei>(sizeof(MeshVertexDataFormat));

        // Position
        {
            constexpr GLuint    vertex_position_location = 0;
            constexpr GLuint    element_count = 2;
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
