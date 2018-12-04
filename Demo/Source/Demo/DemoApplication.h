#ifndef DEMO_APPLICATION_H_
#define DEMO_APPLICATION_H_

// Library includes

// External includes

// Engine includes
#include "Application\SDLApplication.h"

// Forward declarations
namespace engine {
namespace events {
    class KeyboardEvent;
}
}

class DemoApplication : public engine::application::SDLApplication
{
public:
    DemoApplication() : engine::application::SDLApplication("Renderer Demo")
    {}
    virtual ~DemoApplication() = default;

    // ApplicationInterface implementation
public:
    bool Init() override;
    void OnKeyboardEvent(const engine::events::KeyboardEvent& i_event) override;

    // Demo functions
private:
    void TestCompileShaders();

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
