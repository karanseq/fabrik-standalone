// Library includes

// External includes

// Engine includes
#include <Graphics/GLUTHelper.h>
#include <Renderer/Renderer.h>

// Demo includes
#include <Demo/DemoApplication.h>

//~====================================================================================================
// MAIN

int main(int argc, char** argv)
{
    DemoApplication demo;
    demo.Init(argc, argv);
    demo.Run();
    return 0;
}
