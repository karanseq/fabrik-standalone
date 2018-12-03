#include "Events/KeyboardEvent.h"

// Engine includes
#include "Data/HashedString.h"

namespace engine {
namespace events {

const SDL_Event& KeyboardEvent::GetSDLEvent() const
{
    return sdl_event_;
}

engine::input::InputType KeyboardEvent::GetInputType()
{
    return input::InputType::INPUT_TYPE_KEYBOARD;
}

const engine::data::HashedString& KeyboardEvent::GetEventID()
{
    static engine::data::HashedString event_id("KeyboardEvent");
    return event_id;
}

} // namespace events
} // namespace engine