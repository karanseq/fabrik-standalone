#include "Demo\DemoApplication.h"

// Library includes

// External includes
#include "GL/glew.h"
#include "SDL.h"

// Engine includes
#include "Data/PooledString.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "Common/Engine.h"
#include "Events/MouseButtonEvent.h"
#include "Graphics/Color.h"
#include "Graphics/Mesh.h"
#include "Graphics/Program.h"
#include "Graphics/Renderer.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"
#include "Math/MathUtil.h"
#include "Math/Mat44.h"
#include "Math/Quaternion.h"
#include "Math/Transform.h"
#include "Math/Vec3D.h"
#include "Memory/SharedPointer.h"
#include "Time/Updater.h"
#include "Util/FileUtils.h"

engine::graphics::Program g_program;
engine::memory::SharedPointer<engine::graphics::Camera> g_camera;
engine::graphics::CameraController g_camera_controller;

constexpr uint8_t g_num_cubes = 9;
engine::graphics::Mesh g_cube;
engine::math::Transform g_cube_transforms[g_num_cubes * g_num_cubes];

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
        g_camera = new engine::graphics::Camera();
        g_camera->Initialize(engine::graphics::Camera::DEFAULT_FOV, float(window_width_) / float(window_height_));
        g_camera->SetPosition(engine::math::Vec3D(0.0f, 0.0f, -10.0f));
        g_camera_controller.SetCamera(g_camera);
    }

    // Initialize the shapes
    {
        constexpr float offset = 7.0f;
        g_cube.Initialize("");
        for (uint8_t i = 0; i < g_num_cubes * g_num_cubes; ++i)
        {
            g_cube_transforms[i].SetPosition(engine::math::Vec3D(i % g_num_cubes * offset, 0.0f, i / g_num_cubes * -offset));
        }
    }

    engine::time::Updater::Get()->AddTickable(this);

    return true;
}

void DemoApplication::Tick(float /*dt*/)
{
    static engine::graphics::Renderer* renderer = engine::graphics::Renderer::Get();
    renderer->SubmitCamera(*g_camera);
    for (const engine::math::Transform& transform : g_cube_transforms)
    {
        renderer->SubmitMesh(g_cube, g_program, transform);
    }
}

void DemoApplication::OnMouseEvent(const engine::events::MouseButtonEvent& i_event)
{

}

void DemoApplication::OnKeyboardEvent(const engine::events::KeyboardEvent& i_event)
{

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
