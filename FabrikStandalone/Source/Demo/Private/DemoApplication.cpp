#include "Demo/DemoApplication.h"

// Library includes

// External includes

// Engine includes

bool DemoApplication::Init(int argc, char** argv)
{
    window_title_ = "FABRIK Standalone";
    return GLApplication::Init(argc, argv);
}

bool DemoApplication::Shutdown()
{
    return GLApplication::Shutdown();
}

void DemoApplication::Update()
{
    GLApplication::Update();
}

void DemoApplication::Render()
{
    GLApplication::Render();
}

void DemoApplication::ReceiveKeyboardInput(unsigned char key, int x, int y)
{
    static constexpr unsigned char ESC_KEY = 27;

    if (key == ESC_KEY)
    {
        Shutdown();
    }
}

