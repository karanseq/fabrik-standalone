#include "Common\Engine.h"

// library includes
#include <stdlib.h>
// TODO: Resolve conflict with namespace time
//#include <time.h>

// engine includes
#include "Data\StringPool.h"
//#include "Events\EventDispatcher.h"
#include "Graphics\Renderer.h"
//#include "Input\Input.h"
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

    //// create job system
    //engine::jobs::JobSystem* job_system = engine::jobs::JobSystem::Create();
    //job_system->CreateTeam(engine::data::PooledString("EngineTeam"), 5);

    // create file util
    engine::util::FileUtils::Create();

//    // initialize input
//    engine::input::StartUp();
//
//    // create event dispatcher
//    engine::events::EventDispatcher::Create();
//
//    // create updater
//    engine::time::Updater::Create();
//
//    // create collider
//    engine::physics::Collider::Create();
//
//    // create physics
//    engine::physics::Physics::Create();
//
//    // create renderer
//    engine::render::Renderer::Create();
//
//#if defined(ENABLE_PROFILING)
//    // create profiler
//    engine::util::Profiler::Create();
//#endif

    // give rand a new seed
    // TODO: Resolve conflict with namespace time
    //srand(static_cast<unsigned int>(time(0)));

    is_paused_ = false;
}

void Update()
{
    //// calculate the ideal delta to run at 60 FPS
    //static const float ideal_dt = 1000.0f / 60.0f;

    //// get delta
    //float dt = engine::time::TimerUtil::CalculateLastFrameTime_ms();

    //// ensure we have a steady 60 frames per second
    //const float diff_dt = ideal_dt - dt;
    //LOG("%s dt:%f diff_dt:%f", __FUNCTION__, dt, diff_dt);
    //engine::time::TimerUtil::CustomSleep(uint32_t(diff_dt > 0.0f ? diff_dt : 0.0f));

    //// save pointers to the modules that need ticking
    //static engine::time::Updater* updater = engine::time::Updater::Get();
    //static engine::physics::Collider* collider = engine::physics::Collider::Get();
    //static engine::physics::Physics* physics = engine::physics::Physics::Get();
    //static engine::render::Renderer* renderer = engine::render::Renderer::Get();

    //// update modules
    //if (!is_paused_)
    //{
    //    updater->Run(dt);
    //    collider->Run(dt);
    //    physics->Run(dt);
    //}
}

void Render()
{
    engine::graphics::Render();
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

#if defined(ENABLE_PROFILING)
    // create profiler
    engine::util::Profiler::Destroy();
#endif

    //// delete renderer
    //engine::render::Renderer::Destroy();

    //// delete physics
    //engine::physics::Physics::Destroy();

    //// delete collider
    //engine::physics::Collider::Destroy();

    //// delete updater
    //engine::time::Updater::Destroy();

    //// delete the event dispatcher
    //engine::events::EventDispatcher::Destroy();

    //// shutdown the input
    //engine::input::Shutdown();

    // delete file util
    engine::util::FileUtils::Destroy();

    //// delete job system
    //engine::jobs::JobSystem::Destroy();

    // delete string pools
    engine::data::StringPool::Destroy();

    // delete allocators
    engine::memory::DestroyAllocators();

#ifdef BUILD_DEBUG
    LOG("---------- %s END ----------", __FUNCTION__);
#endif
}

} // namespace engine