#include "Application/GLApplication.h"

// Library includes

// External includes
#include <GL/freeglut.h>

// Engine includes
#include <Graphics/GLUTHelper.h>
#include <Renderer/Renderer.h>

namespace engine {
namespace application {

    bool GLApplication::Init(int argc, char** argv)
    {
        g_application = this;

        engine::graphics::GLUTHelper::InitParams init_params;
        init_params.pargc = &argc;
        init_params.argv = argv;
        init_params.display_mode = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;

        // Init window parameters
        {
            init_params.window_width = window_width_;
            init_params.window_height = window_height_;
            init_params.window_title = window_title_;
        }

        // Setup callbacks
        {
            init_params.display_func = &engine::application::ApplicationRenderFunc;
            init_params.idle_func = &engine::application::ApplicationUpdateFunc;
            init_params.keyboard_func = &engine::application::ApplicationKeyboardFunc;
        }

        return engine::graphics::GLUTHelper::Init(init_params);
    }

    void GLApplication::Run()
    {
        engine::graphics::GLUTHelper::Run();
    }

    bool GLApplication::Shutdown()
    {
        return engine::graphics::GLUTHelper::Shutdown();
    }

    void GLApplication::Update()
    {
        engine::renderer::Update();
    }

    void GLApplication::Render()
    {
        engine::renderer::Render();
    }

    void GLApplication::ReceiveKeyboardInput(unsigned char key, int x, int y)
    {
        // no operation
    }

} // namespace application
} // namespace engine
