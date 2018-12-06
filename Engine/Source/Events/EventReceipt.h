#ifndef EVENT_RECEIPT_H_
#define EVENT_RECEIPT_H_

// Engine includes
#include "Data/HashedString.h"

namespace engine {
namespace events {

class EventReceipt
{
public:
    EventReceipt() :
        event_id_("invalid"),
        listener_id_(0)
    {}
    EventReceipt(const engine::data::HashedString& i_event_id, size_t i_listener_id) :
        event_id_(i_event_id),
        listener_id_(i_listener_id)
    {}
    ~EventReceipt() = default;

    EventReceipt(const EventReceipt&) = default;
    EventReceipt(EventReceipt&&) = default;

    EventReceipt& operator=(const EventReceipt&) = default;
    EventReceipt& operator=(EventReceipt&&) = default;

    inline bool operator==(const EventReceipt& i_other) const;
    inline bool operator!=(const EventReceipt& i_other) const;

    inline const engine::data::HashedString& GetEventID() const;

    inline bool IsValid() const;
    inline void Invalidate();

private:
    engine::data::HashedString                                                  event_id_;
    size_t                                                                      listener_id_;
}; // class EventReceipt

} // namespace events
} // namespace engine

#include "EventReceipt-inl.h"

#endif // EVENT_RECEIPT_H_