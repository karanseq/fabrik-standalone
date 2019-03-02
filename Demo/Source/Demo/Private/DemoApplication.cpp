#include "Demo\DemoApplication.h"

// Library includes

// External includes
#include "GL\glew.h"
#include "SDL.h"

// Engine includes
#include "Data\PooledString.h"
#include "Events\MouseButtonEvent.h"
#include "Input\InputProcessor.h"
#include "Logger\Logger.h"
#include "Util\FileUtils.h"

bool DemoApplication::Init()
{
    if (engine::application::SDLApplication::Init() == false)
    {
        return false;
    }

    mouse_event_receipt_ = engine::input::InputProcessor::Get()->AddListener(
        std::bind(&DemoApplication::OnMouseEvent, this, std::placeholders::_1)
        );
    if (mouse_event_receipt_.IsValid() == false)
    {
        LOG_ERROR("Couldn't add a mouse event listener!");
        return false;
    }

    return true;
}

void DemoApplication::OnMouseEvent(const engine::events::MouseButtonEvent& i_event)
{
    const SDL_MouseButtonEvent& sdl_event = i_event.GetSDLEvent();
    LOG("%s TYPE:%s BUTTON:%d X:%d Y:%d",
        __FUNCTION__, (sdl_event.type == SDL_MOUSEBUTTONDOWN ? "DOWN" : "UP"), sdl_event.button, sdl_event.x, sdl_event.y);
}
