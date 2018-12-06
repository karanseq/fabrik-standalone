#include "EventReceipt.h"

namespace engine {
namespace events {

inline bool EventReceipt::operator==(const EventReceipt& i_other) const
{
    return event_id_ == i_other.event_id_ && listener_id_ == i_other.listener_id_;
}

inline bool EventReceipt::operator!=(const EventReceipt& i_other) const
{
    return event_id_ != i_other.event_id_ || listener_id_ != i_other.listener_id_;
}

inline const engine::data::HashedString& EventReceipt::GetEventID() const
{
    return event_id_;
}

inline bool EventReceipt::IsValid() const
{
    return listener_id_ != 0;
}

inline void EventReceipt::Invalidate()
{
    static const engine::data::HashedString invalid("invalid");
    event_id_ = invalid;
    listener_id_ = 0;
}

} // namespace events
} // namespace engine
