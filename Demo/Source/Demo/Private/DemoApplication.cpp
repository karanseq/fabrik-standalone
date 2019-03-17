#include "Demo\DemoApplication.h"

// Library includes

// External includes
#include "GL/glew.h"
#include "SDL.h"

// Engine includes
#include "Data/PooledString.h"
#include "Common/Engine.h"
#include "Events/MouseButtonEvent.h"
#include "Graphics/Camera.h"
#include "Graphics/Color.h"
#include "Graphics/Mesh.h"
#include "Graphics/Program.h"
#include "Graphics/Renderer.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"
#include "Math/MathUtil.h"
#include "Math/Mat44.h"
#include "Math/Transform.h"
#include "Math/Vec3D.h"
#include "Time/Updater.h"
#include "Util/FileUtils.h"

engine::graphics::Program g_program;
engine::graphics::Camera g_camera;
engine::graphics::Mesh g_cube;

engine::math::Transform g_model_transform;

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

    // Initialize the camera
    {
        g_camera.Initialize(engine::graphics::Camera::DEFAULT_FOV, float(window_width_) / float(window_height_));
        engine::math::Transform camera_transform = g_camera.GetTransform();
        camera_transform.SetPosition(engine::math::Vec3D(0.0f, 0.0f, -10.0f));
        g_camera.SetTransform(camera_transform);
    }

    g_cube.Initialize("");

    engine::time::Updater::Get()->AddTickable(this);

    return true;
}

void DemoApplication::Tick(float /*dt*/)
{
    // Update based on input
    {
        static constexpr float camera_speed = 0.1f;
        const engine::math::Vec3D camera_delta(
            (is_left_pressed_ ? camera_speed : (is_right_pressed_ ? -camera_speed : 0.0f)),
            (is_up_pressed_ ? -camera_speed : (is_down_pressed_ ? camera_speed : 0.0f)),
            (is_forward_pressed_ ? camera_speed : (is_back_pressed_ ? -camera_speed : 0.0f))
        );
        g_camera.SetPosition(g_camera.GetPosition() + camera_delta);
    }

    // Submit stuff to be rendered
    {
        static engine::graphics::Renderer* renderer = engine::graphics::Renderer::Get();
        renderer->SubmitCamera(g_camera);
        renderer->SubmitMesh(g_cube, g_program, g_model_transform);
    }
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

    if (g_program.Initialize(vertex_shader_file_path, fragment_shader_file_path) == false)
    {
        LOG_ERROR("Failed to initialize the graphics program. Check above for details.");
        engine::RequestShutdown();
    }
}
