#include <nspl/event/Event.h>
#include <nspl/event/EventVisitor.h>
namespace NSPL
{
    void KeyDownEvent::accept(EventVisitor& visitor) {
        visitor.visit(*this);
    }

    void MouseMoveEvent::accept(EventVisitor& visitor) {
        visitor.visit(*this);
    }

    void QuitEvent::accept(EventVisitor& visitor) {
        visitor.visit(*this);
    }
} // namespace NSPL
