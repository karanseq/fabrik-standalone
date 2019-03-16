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
#include "Graphics/Mesh.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"
#include "Math/MathUtil.h"
#include "Math/Mat44.h"
#include "Math/Transform.h"
#include "Math/Vec3D.h"
#include "Util/FileUtils.h"

engine::graphics::Mesh g_cube;

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
    InitTransforms();
    g_cube.Initialize("");

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

    g_cube.Draw();
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
    LOG("%s KEY:%d", __FUNCTION__, sdl_event.keysym.sym);
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

void DemoApplication::InitTransforms()
{
    const engine::math::Vec3D camera_position = g_camera_transform.GetPosition() + 
                                                engine::math::Vec3D(0.0f, 0.0f, -10.0f);
    g_camera_transform.SetPosition(camera_position);
    engine::math::GetObjectToWorldTransform(g_camera_transform, g_camera_matrix);

    engine::math::GetObjectToWorldTransform(g_model_transform, g_model_matrix);

    static constexpr float  fov = float(engine::math::PI) * 0.25f;
    static const float      aspect_ratio = float(window_width_) / float(window_height_);
    static constexpr float  near_plane = 0.1f;
    static constexpr float  far_plane = 1000.0f;
    g_projection_matrix = engine::math::Mat44::GetPerspectiveProjection(fov, aspect_ratio, near_plane, far_plane);
}
