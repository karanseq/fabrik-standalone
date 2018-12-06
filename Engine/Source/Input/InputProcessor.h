#ifndef INPUT_PROCESSOR_H_
#define INPUT_PROCESSOR_H_

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

    void HandleSDLEvent(const SDL_Event& i_sdl_event);
    void Update();

    inline engine::events::EventReceipt AddListener(const engine::events::CallbackType<engine::events::KeyboardEvent>& i_listener);
    inline engine::events::EventReceipt AddListener(const engine::events::CallbackType<engine::events::MouseButtonEvent>& i_listener);
    inline void RemoveListener(engine::events::EventReceipt& io_receipt);

private:
    inline bool IsReceiptValid(const engine::events::EventReceipt& i_receipt) const;

    void RemoveListeners();

private:
    InputProcessor() = default;
    ~InputProcessor() = default;
    static InputProcessor*                                              instance_;

    InputProcessor(const InputProcessor&) = delete;
    InputProcessor(InputProcessor&&) = delete;
    InputProcessor& operator=(const InputProcessor&) = delete;
    InputProcessor& operator=(InputProcessor&&) = delete;

private:
    engine::events::EventDispatcher<engine::events::KeyboardEvent>      keyboard_event_dispatcher_;
    engine::events::EventDispatcher<engine::events::MouseButtonEvent>   mouse_event_dispatcher_;
    std::vector<SDL_Event>                                              events_this_frame_;
    std::vector<engine::events::EventReceipt>                           listeners_to_remove_;

}; // class InputProcessor

} // namespace input
} // namespace engine

#include "InputProcessor-inl.h"

#endif // INPUT_PROCESSOR_H_
