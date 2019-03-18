#include "InputProcessor.h"

// Engine includes
#include "Data/HashedString.h"
#include "Logger/Logger.h"

namespace engine {
namespace input {

// Mouse button

inline bool InputProcessor::IsLeftMouseButtonPressed(const SDL_MouseButtonEvent& i_event)
{
    return i_event.state == SDL_PRESSED && i_event.button == SDL_BUTTON_LEFT;
}

inline bool InputProcessor::IsRightMouseButtonPressed(const SDL_MouseButtonEvent& i_event)
{
    return i_event.state == SDL_PRESSED && i_event.button == SDL_BUTTON_RIGHT;
}

// Mouse motion

inline int32_t InputProcessor::GetCurrentMouseX() const
{
    return current_mouse_motion_.x;
}

inline int32_t InputProcessor::GetCurrentMouseY() const
{
    return current_mouse_motion_.y;
}

inline int32_t InputProcessor::GetPreviousMouseX() const
{
    return previous_mouse_motion_.x;
}

inline int32_t InputProcessor::GetPreviousMouseY() const
{
    return previous_mouse_motion_.y;
}

// Listeners and event dispatchers

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
