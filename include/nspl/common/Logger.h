#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace NSPL
{
    class Logger{
        public:
            static void Init();
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_AppLogger;
    };
} // namespace NSPL

// Core logger macros
#define CORE_TRACE(...) NSPL::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) NSPL::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) NSPL::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) NSPL::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) NSPL::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// App logger macros
#define APP_TRACE(...) NSPL::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define APP_INFO(...) NSPL::Logger::GetAppLogger()->info(__VA_ARGS__)
#define APP_WARN(...) NSPL::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...) NSPL::Logger::GetAppLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...) NSPL::Logger::GetAppLogger()->critical(__VA_ARGS__)

// Fatal macros
#define CORE_FATAL(...) \
    do { \
        NSPL::Logger::GetCoreLogger()->critical(__VA_ARGS__); \
        std::exit(-1); \
    } while(0)

#define FATAL(...) \
    do { \
        NSPL::Logger::GetAppLogger()->critical(__VA_ARGS__); \
        std::exit(-1); \
    } while(0)
