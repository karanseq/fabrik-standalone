#include "Application/SDLApplication.h"

// Library includes
#ifdef BUILD_DEBUG
#include <crtdbg.h>
#endif // BUILD_DEBUG

// External includes

// Engine includes
#include "Common/Engine.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseButtonEvent.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"

namespace engine {
namespace application {

// Static member initialization
ApplicationInterface* ApplicationInterface::g_application = nullptr;

SDLApplication::SDLApplication(const char* i_window_title) :
    window_title_(i_window_title)
{}

bool SDLApplication::Init()
{
    g_application = this;

    // SDL Init
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("Failed to init SDL! Error:%s", SDL_GetError());
        return false;
    }

    // Window and context creation
    {
        window_ = SDL_CreateWindow(window_title_,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width_,
            window_height_,
            SDL_WINDOW_OPENGL);

        if (window_ == nullptr)
        {
            LOG_ERROR("Failed to create a window! Error:%s", SDL_GetError());
            return false;
        }
    }

    if (engine::Init(window_) == false)
    {
        return false;
    }

    if (InitInputEventDispatchers() == false)
    {
        return false;
    }

    return true;
}

void SDLApplication::Run()
{
    while (WasShutdownRequested() == false)
    {
        engine::Update();
        engine::Render();
    }
}

void SDLApplication::Shutdown()
{
    engine::Shutdown();

    SDL_DestroyWindow(window_);
    SDL_Quit();

#if defined(_DEBUG)
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
}

bool SDLApplication::InitInputEventDispatchers()
{
    keyboard_event_receipt_ = engine::input::InputProcessor::Get()->AddListener(
        std::bind(&SDLApplication::OnKeyboardEvent, this, std::placeholders::_1)
        );
    if (keyboard_event_receipt_.IsValid() == false)
    {
        LOG_ERROR("Couldn't add a keyboard event listener!");
        return false;
    }

    return true;
}

void SDLApplication::OnKeyboardEvent(const engine::events::KeyboardEvent& i_event)
{
    const SDL_KeyboardEvent& sdl_event = i_event.GetSDLEvent();
    const SDL_Keycode keycode = sdl_event.keysym.sym;
    if (keycode == SDLK_ESCAPE)
    {
        RequestShutdown();
    }
}

} // namespace application
} // namespace engine
