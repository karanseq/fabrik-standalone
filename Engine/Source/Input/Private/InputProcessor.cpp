#include "Input/InputProcessor.h"

// Library includes

// Engine includes
#include "Common/Engine.h"
#include "Common/HelperMacros.h"

namespace engine {
namespace input {

// Static member initialization
InputProcessor* InputProcessor::instance_ = nullptr;

InputProcessor* InputProcessor::Create()
{
    if (InputProcessor::instance_ == nullptr)
    {
        InputProcessor::instance_ = new InputProcessor();
    }
    return InputProcessor::instance_;
}

void InputProcessor::Destroy()
{
    SAFE_DELETE(InputProcessor::instance_);
}

// Listeners and event dispatchers

void InputProcessor::RemoveListeners()
{
    for (engine::events::EventReceipt& receipt : listeners_to_remove_)
    {
        if (receipt.GetEventID() == engine::events::KeyboardEvent::GetEventID())
        {
            keyboard_event_dispatcher_.RemoveListener(receipt);
        }
        else if (receipt.GetEventID() == engine::events::MouseButtonEvent::GetEventID())
        {
            mouse_event_dispatcher_.RemoveListener(receipt);
        }
    }

    listeners_to_remove_.clear();
}

// Internal

void InputProcessor::Update()
{
    events_this_frame_.clear();
    previous_mouse_motion_ = current_mouse_motion_;

    // Accumulate all supported SDL events
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                events_this_frame_.push_back(event);
                break;

            case SDL_QUIT:
                engine::RequestShutdown();
                break;

            case SDL_MOUSEMOTION:
                current_mouse_motion_ = event.motion;
                break;

            default:
                break;
            }
        }
    }

    // Dispatch events
    for (const auto& sdl_event : events_this_frame_)
    {
        switch (sdl_event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyboard_event_dispatcher_.DispatchEvent(engine::events::KeyboardEvent(sdl_event.key));
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            mouse_event_dispatcher_.DispatchEvent(engine::events::MouseButtonEvent(sdl_event.button));
            break;

        default:
            break;
        }
    }

    // Clear after dispatch
    if (listeners_to_remove_.empty() == false)
    {
        RemoveListeners();
    }
}

} // namespace input
} // namespace engine

