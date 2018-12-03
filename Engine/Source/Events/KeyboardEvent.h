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

class KeyboardEvent
{
public:
    KeyboardEvent(const SDL_Event& i_sdl_event) :
        sdl_event_(i_sdl_event)
    {}
    ~KeyboardEvent() = default;

    const SDL_Event& GetSDLEvent() const;

    static engine::input::InputType GetInputType();
    static const engine::data::HashedString& GetEventID();

private:
    const SDL_Event&                       sdl_event_;

}; // class KeyboardEvent

} // namespace events
} // namespace engine

#endif // KEYBOARD_EVENT_H_