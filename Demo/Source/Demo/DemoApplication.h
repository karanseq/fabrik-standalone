#ifndef DEMO_APPLICATION_H_
#define DEMO_APPLICATION_H_

// Library includes

// External includes

// Engine includes
#include "Application\SDLApplication.h"

class DemoApplication : public engine::application::SDLApplication
{
public:
    DemoApplication() : engine::application::SDLApplication("Renderer Demo")
    {}
    virtual ~DemoApplication() = default;

    // Demo functions
private:
    void TestCompileShaders();

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
