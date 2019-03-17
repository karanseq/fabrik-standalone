#include "Time/Updater.h"

// Engine includes
#include "Assert/Assert.h"
#include "Common/HelperMacros.h"
#include "Logger/Logger.h"
#include "Time/InterfaceTickable.h"

namespace engine {
namespace time {

// Static member initialization
Updater* Updater::instance_ = nullptr;

Updater* Updater::Create()
{
    if (!Updater::instance_)
    {
        Updater::instance_ = new Updater();
    }
    return Updater::instance_;
}

void Updater::Destroy()
{
    SAFE_DELETE(Updater::instance_);
}

void Updater::AddTickable(InterfaceTickable* i_tickable)
{
    // validate input
    ASSERT(i_tickable);

    // check if this object already exists
    if (std::find(tickables_.begin(), tickables_.end(), i_tickable) != tickables_.end())
    {
        LOG_ERROR("Updater is already tracking this tickable!");
        return;
    }

    tickables_.push_back(i_tickable);
}

void Updater::RemoveTickable(InterfaceTickable* i_tickable)
{
    // validate input
    ASSERT(i_tickable);
    // can't remove an object if there are none
    ASSERT(tickables_.size() > 0);

    // check if this object exists
    auto it = std::find(tickables_.begin(), tickables_.end(), i_tickable);
    if (it == tickables_.end())
    {
        LOG_ERROR("Updater could not find this tickable!");
        return;
    }
    tickables_.erase(it);
}

void Updater::Update(float dt) const
{
    // tick all tickables
    for (size_t i = 0; i < tickables_.size(); ++i)
    {
        tickables_[i]->Tick(dt);
    }
}

} // namespace time
} // namespace engin