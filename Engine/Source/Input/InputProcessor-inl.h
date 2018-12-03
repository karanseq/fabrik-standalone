#include "InputProcessor.h"

// Engine includes
#include "Data/HashedString.h"
#include "Logger/Logger.h"

namespace engine {
namespace input {

template<typename T>
inline engine::events::EventReceipt InputProcessor::AddListener(const engine::events::CallbackType<T>& i_listener)
{
    if (engine::events::EventDispatcher<T>* event_dispatcher = GetEventDispatcher<T>())
    {
        return event_dispatcher->AddListener(i_listener);
    }
    else
    {
        LOG_ERROR("%s couldn't find an appropriate event dispatcher!", __FUNCTION__);
        return engine::events::EventReceipt();
    }
}

template<typename T>
inline void InputProcessor::RemoveListener(engine::events::EventReceipt& i_receipt)
{
    if (IsValidReceipt(i_receipt))
    {
        listeners_to_remove_.push_back(i_receipt);
        i_receipt.Invalidate();
    }
    else
    {
        LOG_ERROR("Invalid event receipt passed to %s", __FUNCTION__);
    }
}

template<typename T>
inline void InputProcessor::DispatchEvent(const T& i_event)
{
    if (engine::events::EventDispatcher<T>* event_dispatcher = GetEventDispatcher<T>())
    {
        event_dispatcher->DispatchEvent(i_event);
    }
    else
    {
        LOG_ERROR("%s couldn't find an appropriate event dispatcher!", __FUNCTION__);
    }
}

template<typename T>
inline engine::events::EventDispatcher<T>* InputProcessor::GetEventDispatcher()
{
    switch (T::GetInputType())
    {
    case InputType::INPUT_TYPE_KEYBOARD:
        return &keyboard_event_dispatcher_;
    default:
        LOG_ERROR("Invalid input type:%d passed to %s", T::GetInputType(), __FUNCTION__);
        return nullptr;
        break;
    }
}

inline bool InputProcessor::IsValidReceipt(const engine::events::EventReceipt& i_receipt) const
{
    const unsigned int keyboard_event_hash = engine::events::KeyboardEvent::GetEventID().GetHash();

    const unsigned int receipt_event_hash = i_receipt.GetEventID().GetHash();
    return (i_receipt.IsValid() &&
        (receipt_event_hash == keyboard_event_hash));
}

} // namespace input
} // namespace engine
