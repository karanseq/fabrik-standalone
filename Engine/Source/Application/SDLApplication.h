#ifndef SDL_APPLICATION_H_
#define SDL_APPLICATION_H_

// Library includes
#include <stdint.h>

// External includes
#include "SDL.h"

// Engine includes
#include "Application/Application.h"
#include "Events/EventReceipt.h"

// Forward declarations
namespace engine {
namespace events {
    class KeyboardEvent;
}
}

namespace engine {
namespace application {

class SDLApplication : public ApplicationInterface
{
public:
    SDLApplication() = default;
    SDLApplication(const char* i_window_title);
    virtual ~SDLApplication() = default;

    // ApplicationInterface implementation
public:
    bool Init() override;
    void Run() override;
    void Shutdown() override;

    // Implementation
private:
    bool InitInputEventDispatchers();
    void OnKeyboardEvent(const engine::events::KeyboardEvent& i_event);

    // Data
protected:
    const uint16_t                          window_width_ = 800;
    const uint16_t                          window_height_ = 600;
    const char*                             window_title_ = "SDL Application";

private:
    SDL_Window*                             window_ = nullptr;
    engine::events::EventReceipt            keyboard_event_receipt_;

}; // class SDLApplication

} // namespace application
} // namespace engine

#endif // SDL_APPLICATION_H_
