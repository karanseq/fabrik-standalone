#include "Input/InputProcessor.h"

// Library includes
#include <functional>
#include <unordered_map>
#include <vector>

// Engine includes

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

void InputProcessor::HandleSDLEvent(const SDL_Event& i_sdl_event)
{
    switch (i_sdl_event.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEMOTION:
        events_this_frame_.push_back(i_sdl_event);
    default:
        break;
    }
}

void InputProcessor::Update()
{
    // Dispatch events
    for (const auto& sdl_event : events_this_frame_)
    {
        switch (sdl_event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            DispatchEvent(engine::events::KeyboardEvent(sdl_event));
            break;
        default:
            break;
        }
    }
    events_this_frame_.clear();

    if (listeners_to_remove_.empty() == false)
    {
        RemoveListeners();
    }
}

void InputProcessor::RemoveListeners()
{
    const unsigned int keyboard_event_hash = engine::events::KeyboardEvent::GetEventID().GetHash();

    for (engine::events::EventReceipt& receipt : listeners_to_remove_)
    {
        const unsigned int receipt_event_hash = receipt.GetEventID().GetHash();
        if (receipt_event_hash == keyboard_event_hash)
        {
            keyboard_event_dispatcher_.RemoveListener(receipt);
        }
    }

    listeners_to_remove_.clear();
}

} // namespace input
} // namespace engine

