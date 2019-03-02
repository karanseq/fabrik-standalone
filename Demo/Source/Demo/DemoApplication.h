#ifndef DEMO_APPLICATION_H_
#define DEMO_APPLICATION_H_

// Library includes

// External includes

// Engine includes
#include "Application\SDLApplication.h"

// Forward declarations
namespace engine {
namespace events {
    class MouseButtonEvent;
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

    // Demo functions
private:
    void OnMouseEvent(const engine::events::MouseButtonEvent& i_event);

    // Data
private:
    engine::events::EventReceipt            mouse_event_receipt_;

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
