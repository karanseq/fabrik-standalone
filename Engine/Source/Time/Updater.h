#ifndef ENGINE_TIME_UPDATER_H_
#define ENGINE_TIME_UPDATER_H_

// System includes
#include <vector>

namespace engine {
namespace time {

// Forward declarations
class InterfaceTickable;

/*
    Updater
    - A singleton that receives ticks from the engine and broadcasts the same to all objects that implement InterfaceTickable
    - Classes that wish to receive ticks must implement InterfaceTickable and add themselves to the Updater
    - Classes that wish to no longer receive ticks must remove themselves from the Updater
*/

class Updater
{
public:
    static Updater* Create();
    static void Destroy();
    static Updater* Get() { return instance_; }

    // Add/remove a tickable
    // TODO: Use subscriber-receipt pattern
    void AddTickable(InterfaceTickable* i_tickable);
    void RemoveTickable(InterfaceTickable* i_tickable);

    // The tick
    void Update(float dt) const;

private:
    std::vector<InterfaceTickable*>             tickables_;

private:
    Updater() = default;
    ~Updater() = default;
    static Updater* instance_;

    Updater(const Updater&) = delete;
    Updater& operator=(const Updater&) = delete;

}; // class Updater

} // namespace time
} // namespace engine

#endif // ENGINE_TIME_UPDATER_H_
