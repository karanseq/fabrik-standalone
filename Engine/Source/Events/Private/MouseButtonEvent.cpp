#include "Events/MouseButtonEvent.h"

// Engine includes
#include "Data/HashedString.h"
#include "Events/EventReceipt.h"

namespace engine {
namespace events {

const SDL_MouseButtonEvent& MouseButtonEvent::GetSDLEvent() const
{
    return sdl_event_;
}

engine::input::InputType MouseButtonEvent::GetInputType()
{
    return input::InputType::INPUT_TYPE_MOUSE;
}

const engine::data::HashedString& MouseButtonEvent::GetEventID()
{
    static engine::data::HashedString event_id("MouseEvent");
    return event_id;
}

bool engine::events::MouseButtonEvent::IsReceiptApplicable(const engine::events::EventReceipt& i_receipt)
{
    return GetEventID() == i_receipt.GetEventID();
}

} // namespace events
} // namespace engine