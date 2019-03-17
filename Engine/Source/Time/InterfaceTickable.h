#ifndef ENGINE_TIME_INTERFACE_TICKABLE_H_
#define ENGINE_TIME_INTERFACE_TICKABLE_H_

namespace engine {
namespace time {

/*
    InterfaceTickable
    - An interface that allows the implementers to receive ticks from the engine.
*/

class InterfaceTickable
{
public:
    virtual ~InterfaceTickable() = default;

    virtual void Tick(float dt) = 0;

}; // class InterfaceTickable

} // namespace time
} // namespace engine

#endif // ENGINE_TIME_INTERFACE_TICKABLE_H_
