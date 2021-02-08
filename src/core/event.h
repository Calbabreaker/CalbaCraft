// clang-format off
enum class EventType
{
    None = 0,
    WindowClosed
};

struct Event
{
    virtual EventType getEventType() const = 0;
    virtual ~Event() = default;
};

class EventDispatcher
{
public:
    EventDispatcher(const Event& event) : m_event(event) {}

    template <typename T, typename EventFunc>
    void dispatch(const EventFunc& func)
    {
        if (m_event.getEventType() == T::getStaticType())
            func(static_cast<const T&>(m_event));
    }

private:
    const Event& m_event;
};

#define MAKE_EVENT_CLASS_TYPE(type)                                                                                    \
    static constexpr EventType getStaticType() { return EventType::type; }                                                       \
    EventType getEventType() const override { return getStaticType(); } 

// window events
struct WindowClosedEvent : public Event
{
    MAKE_EVENT_CLASS_TYPE(WindowClosed)
};
