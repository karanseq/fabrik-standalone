#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

// Library includes
#include <functional>
#include <mutex>
#include <unordered_map>
#include <vector>

// Engine includes
#include "Data/HashedString.h"
#include "Memory/SharedPointer.h"
#include "Memory/WeakPointer.h"

namespace engine {
namespace events {

template<typename T>
using CallbackType = std::function<void(const T&)>;

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

template<typename T>
class EventDispatcher
{
public:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;

    inline EventReceipt AddListener(const CallbackType<T>& i_callback);
    inline void RemoveListener(EventReceipt& i_event_receipt);
    inline void DispatchEvent(const T& i_event);

private:
    struct EventReceiptHash
    {
        std::size_t operator()(const EventReceipt& i_receipt) const
        {
            return static_cast<size_t>(i_receipt.GetEventID().GetHash());
        }
    };

private:
    mutable std::mutex                                                          listeners_mutex_;
    std::unordered_map<EventReceipt, CallbackType<T>, EventReceiptHash>         listeners_;
    size_t                                                                      id_counter_ = 0;
}; // class EventDispatcher

} // namespace events
} // namespace engine

#include "EventDispatcher-inl.h"

#endif // EVENT_DISPATCHER_H_
