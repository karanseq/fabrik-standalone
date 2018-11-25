#include "Application\GLApplication.h"

// Library includes
#ifdef BUILD_DEBUG
#include <crtdbg.h>
#endif // BUILD_DEBUG

// External includes
#include <GL\freeglut.h>

// Engine includes
#include "Application\GLUTHelper.h"
#include "Common\Engine.h"

namespace engine {
namespace application {

    bool GLApplication::Init(int argc, char** argv)
    {
        g_application = this;

        GLUTHelper::InitParams init_params;
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
            init_params.display_func = &ApplicationRenderFunc;
            init_params.idle_func = &ApplicationUpdateFunc;
            init_params.keyboard_func = &ApplicationKeyboardFunc;
        }

        if (GLUTHelper::Init(init_params) == false)
        {
            return false;
        }

        engine::Init();
        return true;
    }

    void GLApplication::Run()
    {
        GLUTHelper::Run();
    }

    bool GLApplication::Shutdown()
    {
        engine::Shutdown();

#if defined(_DEBUG)
        _CrtDumpMemoryLeaks();
#endif // _DEBUG

        return GLUTHelper::Shutdown();
    }

    void GLApplication::Update()
    {
        engine::Update();
        GLUTHelper::Update();
    }

    void GLApplication::Render()
    {
        engine::Render();
    }

    void GLApplication::ReceiveKeyboardInput(unsigned char key, int x, int y)
    {
        // no operation
    }

} // namespace application
} // namespace engine
