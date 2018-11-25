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
    if (demo.Init(argc, argv))
    {
        demo.Run();
    }
    return 0;
}
