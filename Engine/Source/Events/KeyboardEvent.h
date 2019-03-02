#ifndef KEYBOARD_EVENT_H_
#define KEYBOARD_EVENT_H_

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

class KeyboardEvent
{
public:
    KeyboardEvent(const SDL_KeyboardEvent& i_sdl_event);
    ~KeyboardEvent() = default;

    const SDL_KeyboardEvent& GetSDLEvent() const;

    static engine::input::InputType GetInputType();
    static const engine::data::HashedString& GetEventID();
    static bool IsReceiptApplicable(const engine::events::EventReceipt& i_receipt);

private:
    const SDL_KeyboardEvent&                        sdl_event_;

}; // class KeyboardEvent

} // namespace events
} // namespace engine

#endif // KEYBOARD_EVENT_H_