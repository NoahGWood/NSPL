#pragma once
#include <functional>
#include <csignal>
#include <unordered_map>
#include <memory>

#include <gofpp/gofpp.hpp>

#include <nspl/window/Window.hpp>
#include <nspl/event/Event.h>
namespace NSPL
{
    class Application : public gofpp::Singleton<Application> {
        public:
            using UpdateEvent = float;
            // --- Lifecycle ---
            bool Init(const WindowDesc& desc);
            void Run();
            void Shutdown();
            void Quit();

            // --- Event Subscriptions ---
            int SubscribeUpdate(const gofpp::Observable<UpdateEvent>::Handler& handler);
            void UnsubscribeUpdate(int id);
            int SubscribeEvent(const gofpp::Observable<Event>::Handler& handler);
            void UnsubscribeEvent(int id);

        private:
            void OnUpdate(float deltaTime);
            void OnEvent(const Event& event);
            void PollEvents();
        private:
            bool m_Running = false;
            gofpp::Observable<UpdateEvent> m_Updates;
            gofpp::Observable<Event> m_Events;
            std::unordered_map<int, std::unique_ptr<Window>> m_Windows;
    };
} // namespace NSPL
