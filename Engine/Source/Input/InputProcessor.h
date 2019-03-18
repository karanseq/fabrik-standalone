#ifndef ENGINE_INPUT_PROCESSOR_H_
#define ENGINE_INPUT_PROCESSOR_H_

// Library includes
#include <vector>

// External includes
#include "SDL.h"

// Engine includes
#include "Events/EventDispatcher.h"
#include "Events/EventReceipt.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseButtonEvent.h"

namespace engine {
namespace input {

class InputProcessor
{
public:
    static InputProcessor* Create();
    static void Destroy();
    static inline InputProcessor* Get() { return instance_; }

    // Mouse button
public:
    static inline bool IsLeftMouseButtonPressed(const SDL_MouseButtonEvent& i_event);
    static inline bool IsRightMouseButtonPressed(const SDL_MouseButtonEvent& i_event);

    // Mouse motion
public:
    inline int32_t GetCurrentMouseX() const;
    inline int32_t GetCurrentMouseY() const;
    inline int32_t GetPreviousMouseX() const;
    inline int32_t GetPreviousMouseY() const;

private:
    SDL_MouseMotionEvent        current_mouse_motion_;
    SDL_MouseMotionEvent        previous_mouse_motion_;

    // Listeners and event dispatchers
public:
    inline engine::events::EventReceipt AddListener(const engine::events::CallbackType<engine::events::KeyboardEvent>& i_listener);
    inline engine::events::EventReceipt AddListener(const engine::events::CallbackType<engine::events::MouseButtonEvent>& i_listener);
    inline void RemoveListener(engine::events::EventReceipt& io_receipt);

private:
    engine::events::EventDispatcher<engine::events::KeyboardEvent>      keyboard_event_dispatcher_;
    engine::events::EventDispatcher<engine::events::MouseButtonEvent>   mouse_event_dispatcher_;
    std::vector<SDL_Event>                                              events_this_frame_;
    std::vector<engine::events::EventReceipt>                           listeners_to_remove_;

private:
    inline bool IsReceiptValid(const engine::events::EventReceipt& i_receipt) const;
    void RemoveListeners();

    // Internal
public:
    void Update();

private:
    InputProcessor() = default;
    ~InputProcessor() = default;
    static InputProcessor*                                              instance_;

    InputProcessor(const InputProcessor&) = delete;
    InputProcessor(InputProcessor&&) = delete;
    InputProcessor& operator=(const InputProcessor&) = delete;
    InputProcessor& operator=(InputProcessor&&) = delete;

}; // class InputProcessor

} // namespace input
} // namespace engine

#include "InputProcessor-inl.h"

#endif // ENGINE_INPUT_PROCESSOR_H_
