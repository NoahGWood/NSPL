#pragma once
#include <gofpp/gofpp.hpp>
namespace NSPL
{
    struct EventVisitor;

    struct Event : gofpp::Visitable<EventVisitor> {
        virtual ~Event() = default;
    };

    struct KeyDownEvent : Event {
        int keycode;
        bool repeat;
        void accept(EventVisitor& visitor) override;
    };

    struct MouseMoveEvent : Event {
        int x, y;
        int dx, dy;

        void accept(EventVisitor& visitor) override;
    };

    struct QuitEvent : Event {
        void accept(EventVisitor& visitor) override;
    };
} // namespace NSPL
