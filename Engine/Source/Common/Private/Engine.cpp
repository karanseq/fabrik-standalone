#include "Common/Engine.h"

// library includes
#include <stdlib.h>
// TODO: Resolve conflict with namespace time
//#include <time.h>

// engine includes
#include "Data/StringPool.h"
#include "Graphics/Renderer.h"
#include "Input/InputProcessor.h"
#include "Logger/Logger.h"
#include "Memory/AllocatorUtil.h"
#include "Time/TimerUtil.h"
#include "Time/Updater.h"
#include "Util/FileUtils.h"

namespace engine {

static bool g_was_shutdown_requested = false;

bool Init(SDL_Window* i_window)
{
    // create allocators
    memory::CreateAllocators();

    // create renderer
    graphics::Renderer::Create(i_window);

    // create string pools
    data::StringPool::Create();

    // create file util
    util::FileUtils::Create();

    // create updater
    time::Updater::Create();

    // initialize input
    input::InputProcessor::Create();

    g_was_shutdown_requested = false;

    return true;
}

void Update()
{
    static input::InputProcessor* input_processor = input::InputProcessor::Get();
    static time::Updater* updater = time::Updater::Get();

    const float dt = time::TimerUtil::CalculateLastFrameTime_ms();

    input_processor->Update();
    updater->Update(dt);
}

void Render()
{
    static graphics::Renderer* renderer = graphics::Renderer::Get();
    renderer->StartCurrentFrame();
    renderer->Draw();
    renderer->EndCurrentFrame();
}

void RequestShutdown()
{
    if (g_was_shutdown_requested == true)
    {
        return;
    }
    g_was_shutdown_requested = true;
}

bool WasShutdownRequested()
{
    return g_was_shutdown_requested;
}

void Shutdown()
{
#ifdef BUILD_DEBUG
    LOG("---------- %s ----------", __FUNCTION__);
#endif

    // shutdown the input
    input::InputProcessor::Destroy();

    // delete updater
    time::Updater::Destroy();

    // delete file util
    util::FileUtils::Destroy();

    // delete string pools
    data::StringPool::Destroy();

    // delete the renderer
    graphics::Renderer::Destroy();

    // delete allocators
    memory::DestroyAllocators();

#ifdef BUILD_DEBUG
    LOG("---------- %s END ----------", __FUNCTION__);
#endif
}

} // namespace engine