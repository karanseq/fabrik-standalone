#include "Application\GLUTHelper.h"

// External includes
#include <GL\glew.h>
#include <GL\freeglut.h>

// Engine includes
#include "Assert\Assert.h"
#include "Logger\Logger.h"

namespace engine {
namespace application{

    bool GLUTHelper::Init(const InitParams& i_params)
    {
        ASSERT(i_params.argv);
        ASSERT(i_params.window_title);

        glutInit(i_params.pargc, i_params.argv);
        glutInitDisplayMode(i_params.display_mode);
        const int screen_width = glutGet(GLUT_SCREEN_WIDTH);
        const int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

        glutInitWindowPosition(screen_width / 2 - i_params.window_width / 2, screen_height / 2 - i_params.window_height / 2);
        glutInitWindowSize(i_params.window_width, i_params.window_height);
        glutInitContextVersion(3, 3);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        glutCreateWindow(i_params.window_title);
        glEnable(GL_DEPTH_TEST);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            LOG_ERROR("glewInit error:%s", glewGetErrorString(err));
            return false;
        }

        // Setup callbacks
        glutDisplayFunc(i_params.display_func);
        glutIdleFunc(i_params.idle_func);
        glutKeyboardFunc(i_params.keyboard_func);

        return true;
    }

    void GLUTHelper::Run()
    {
        glutMainLoop();
    }

    void GLUTHelper::Update()
    {
        glutPostRedisplay();
    }

    bool GLUTHelper::Shutdown()
    {
        glutLeaveMainLoop();
        return true;
    }

} // namespace application
} // namespace engine
