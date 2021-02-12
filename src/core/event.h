#pragma once

#include <glm/glm.hpp>

// clang-format off
enum class EventType
{
    None = 0,
    WindowClosed,
    MouseMoved
};
// clang-format on

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

#define MAKE_EVENT_CLASS_TYPE(type)                                                                \
    static constexpr EventType getStaticType() { return EventType::type; }                         \
    EventType getEventType() const override { return getStaticType(); }

struct WindowClosedEvent : public Event
{
    MAKE_EVENT_CLASS_TYPE(WindowClosed)
};

struct MouseMovedEvent : public Event
{
    MouseMovedEvent(const glm::vec2& offset) : m_offset(offset) {}

    const glm::vec2& getOffset() const { return m_offset; }

    MAKE_EVENT_CLASS_TYPE(MouseMoved)

private:
    glm::vec2 m_offset;
};
