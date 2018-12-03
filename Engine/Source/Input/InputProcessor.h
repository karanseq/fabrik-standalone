#ifndef INPUT_PROCESSOR_H_
#define INPUT_PROCESSOR_H_

// Library includes

// External includes
#include "SDL.h"

// Engine includes
#include "Events/EventDispatcher.h"
#include "Events/KeyboardEvent.h"
#include "Input/InputTypes.h"

// Forward declarations
namespace engine {
namespace events {
    class KeyboardEvent;
}
}

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

    template<typename T>
    inline engine::events::EventReceipt AddListener(const engine::events::CallbackType<T>& i_listener);
    template<typename T>
    inline void RemoveListener(engine::events::EventReceipt& io_receipt);

private:
    template<typename T>
    inline void DispatchEvent(const T& i_event);
    template<typename T>
    inline engine::events::EventDispatcher<T>* GetEventDispatcher();
    inline bool IsValidReceipt(const engine::events::EventReceipt& i_receipt) const;

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
    std::vector<SDL_Event>                                              events_this_frame_;
    std::vector<engine::events::EventReceipt>                           listeners_to_remove_;

}; // class InputProcessor

} // namespace input
} // namespace engine

#include "InputProcessor-inl.h"

#endif // INPUT_PROCESSOR_H_
