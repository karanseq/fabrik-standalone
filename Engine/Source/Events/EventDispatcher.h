#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

// Library includes
#include <functional>
#include <mutex>
#include <unordered_map>

// Engine includes
#include "Data/HashedString.h"
#include "Events/EventReceipt.h"

namespace engine {
namespace events {

template<typename T>
using CallbackType = std::function<void(const T&)>;

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
