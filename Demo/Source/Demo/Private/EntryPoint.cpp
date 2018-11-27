// Library includes

// External includes

// Engine includes

// Demo includes
#include "Demo\DemoApplication.h"

//~====================================================================================================
// MAIN

int main(int argc, char** argv)
{
    DemoApplication demo;
    if (demo.Init())
    {
        demo.Run();
        demo.Shutdown();
    }
    return 0;
}
