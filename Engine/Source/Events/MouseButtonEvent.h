#ifndef MOUSE_BUTTON_EVENT_H_
#define MOUSE_BUTTON_EVENT_H_

// External includes
#include "SDL_events.h"

// Engine includes
#include "Input/InputTypes.h"

// Forward declarations
namespace engine {
namespace data {
    class HashedString;
}
}

namespace engine {
namespace events {

class EventReceipt;

class MouseButtonEvent
{
public:
    MouseButtonEvent(const SDL_MouseButtonEvent& i_sdl_event);
    ~MouseButtonEvent() = default;

    const SDL_MouseButtonEvent& GetSDLEvent() const;

    static engine::input::InputType GetInputType();
    static const engine::data::HashedString& GetEventID();
    static bool IsReceiptApplicable(const engine::events::EventReceipt& i_receipt);

private:
    const SDL_MouseButtonEvent&                     sdl_event_;

}; // class MouseButtonEvent

} // namespace events
} // namespace engine

#endif // MOUSE_BUTTON_EVENT_H_
