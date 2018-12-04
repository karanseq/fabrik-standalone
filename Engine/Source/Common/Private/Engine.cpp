#include "Common\Engine.h"

// library includes
#include <stdlib.h>
// TODO: Resolve conflict with namespace time
//#include <time.h>

// engine includes
#include "Data\StringPool.h"
#include "Graphics\Renderer.h"
#include "Input\InputProcessor.h"
#include "Logger\Logger.h"
#include "Memory\AllocatorUtil.h"
#include "Util\FileUtils.h"

namespace engine {

static bool g_was_shutdown_requested = false;

bool Init()
{
    // create allocators
    engine::memory::CreateAllocators();

    // create string pools
    engine::data::StringPool::Create();

    // create file util
    engine::util::FileUtils::Create();

    // initialize input
    engine::input::InputProcessor::Create();

    g_was_shutdown_requested = false;

    return true;
}

void Update()
{
    engine::input::InputProcessor::Get()->Update();
}

void Render()
{
    engine::graphics::Render();
}

void HandleSDLEvent(const SDL_Event& i_event)
{
    engine::input::InputProcessor::Get()->HandleSDLEvent(i_event);
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
    engine::input::InputProcessor::Destroy();

    // delete file util
    engine::util::FileUtils::Destroy();

    // delete string pools
    engine::data::StringPool::Destroy();

    // delete allocators
    engine::memory::DestroyAllocators();

#ifdef BUILD_DEBUG
    LOG("---------- %s END ----------", __FUNCTION__);
#endif
}

} // namespace engine