#include "InputProcessor.h"

// Engine includes
#include "Data/HashedString.h"
#include "Logger/Logger.h"

namespace engine {
namespace input {

inline engine::events::EventReceipt InputProcessor::AddListener(const engine::events::CallbackType<engine::events::KeyboardEvent>& i_listener)
{
    return keyboard_event_dispatcher_.AddListener(i_listener);
}

inline engine::events::EventReceipt InputProcessor::AddListener(const engine::events::CallbackType<engine::events::MouseButtonEvent>& i_listener)
{
    return mouse_event_dispatcher_.AddListener(i_listener);
}

inline void InputProcessor::RemoveListener(engine::events::EventReceipt& i_receipt)
{
    if (IsReceiptValid(i_receipt))
    {
        listeners_to_remove_.push_back(i_receipt);
        i_receipt.Invalidate();
    }
    else
    {
        LOG_ERROR("Invalid event receipt passed to %s", __FUNCTION__);
    }
}

inline bool InputProcessor::IsReceiptValid(const engine::events::EventReceipt& i_receipt) const
{
    return (i_receipt.IsValid() && 
        (engine::events::KeyboardEvent::IsReceiptApplicable(i_receipt) || 
            engine::events::MouseButtonEvent::IsReceiptApplicable(i_receipt)));
}

} // namespace input
} // namespace engine
