// Library includes

// External includes
#include <GL/freeglut.h>

// Engine includes
#include "Graphics/GLUTHelper.h"

//~====================================================================================================
// Function declarations

// Callback functions
void DisplayFunc();
void IdleFunc();
void KeyboardFunc(unsigned char key, int x, int y);

//~====================================================================================================
// MAIN

int main(int argcp, char** argv)
{
    // Initialize GLUT
    {
        engine::graphics::GLUTHelper::InitParams init_params;
        init_params.pargc = &argcp;
        init_params.argv = argv;
        init_params.display_mode = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;

        init_params.window_width = 800;
        init_params.window_height = 600;
        init_params.window_title = "FABRIK Standalone";

        init_params.display_func = &DisplayFunc;
        init_params.idle_func = &IdleFunc;
        init_params.keyboard_func = &KeyboardFunc;

        engine::graphics::GLUTHelper::Init(init_params);
    }

    return 0;
}

//~====================================================================================================
// Callback functions

void DisplayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    glutSwapBuffers();
}

void IdleFunc()
{
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    static constexpr unsigned char ESC_KEY = 27;

    if (key == ESC_KEY)
    {
        glutLeaveMainLoop();
    }
}
