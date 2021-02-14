#pragma once

#include <glm/glm.hpp>

// clang-format off
enum class EventType
{
    None = 0,
    WindowClosed, WindowResized,
    KeyPressed,
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

struct WindowResizedEvent : public Event
{
    WindowResizedEvent(uint32_t p_width, uint32_t p_height) : width(p_width), height(p_height) {}

    MAKE_EVENT_CLASS_TYPE(WindowResized)

    const uint32_t width;
    const uint32_t height;
};

struct KeyPressedEvent : public Event
{
    KeyPressedEvent(int p_key) : key(p_key) {}

    MAKE_EVENT_CLASS_TYPE(KeyPressed)

    const int key;
};

struct MouseMovedEvent : public Event
{
    MouseMovedEvent(const glm::vec2& p_offset) : offset(p_offset) {}

    MAKE_EVENT_CLASS_TYPE(MouseMoved)

    const glm::vec2 offset;
};
