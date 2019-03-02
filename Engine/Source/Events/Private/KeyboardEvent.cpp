#include "Events/KeyboardEvent.h"

// Engine includes
#include "Data/HashedString.h"
#include "Events/EventReceipt.h"

namespace engine {
namespace events {

KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& i_sdl_event) :
    sdl_event_(i_sdl_event)
{}

const SDL_KeyboardEvent& KeyboardEvent::GetSDLEvent() const
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

bool KeyboardEvent::IsReceiptApplicable(const engine::events::EventReceipt& i_receipt)
{
    return GetEventID() == i_receipt.GetEventID();
}

} // namespace events
} // namespace engine