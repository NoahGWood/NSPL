#pragma once
#include <gofpp/gofpp.hpp>
#include <nspl/event/Event.h>
namespace NSPL
{
    // EventVisitor interface
    struct EventVisitor : gofpp::Visitor<Event> {
        virtual void visit(KeyDownEvent& e) = 0;
        virtual void visit(MouseMoveEvent& e) = 0;
        virtual void visit(QuitEvent& e) = 0;
    };
} // namespace NSPL
