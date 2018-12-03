#include "Common\Engine.h"

// library includes
#include <stdlib.h>
// TODO: Resolve conflict with namespace time
//#include <time.h>

// engine includes
#include "Data\StringPool.h"
#include "Graphics\Renderer.h"
#include "Input\InputProcessor.h"
//#include "Jobs\JobSystem.h"
#include "Logger\Logger.h"
#include "Memory\AllocatorUtil.h"
//#include "Physics\Collider.h"
//#include "Physics\Physics.h"
//#include "Renderer\Renderer.h"
#include "Time\TimerUtil.h"
//#include "Time\Updater.h"
#include "Util\FileUtils.h"
#include "Util\Profiler.h"

namespace engine {

static bool is_paused_ = false;

void Init()
{
    // create allocators
    engine::memory::CreateAllocators();

    // create string pools
    engine::data::StringPool::Create();

    // create file util
    engine::util::FileUtils::Create();

    // initialize input
    engine::input::InputProcessor::Create();

    is_paused_ = false;
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

void Pause()
{
    if (is_paused_)
    {
        return;
    }
    is_paused_ = true;
}

void Resume()
{
    if (!is_paused_)
    {
        return;
    }
    is_paused_ = false;
}

bool IsPaused()
{
    return is_paused_;
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