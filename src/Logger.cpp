#include <nspl/common/Logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace NSPL {


    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

    void Logger::Init() {
        s_CoreLogger = spdlog::stdout_color_mt("NSPL_CORE");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->set_pattern("[%T] [%^%l%$] %v");

        s_AppLogger = spdlog::stdout_color_mt("NSPL_APP");
        s_AppLogger->set_level(spdlog::level::trace);
        s_AppLogger->set_pattern("[%T] [%^%l%$] %v");
    }

} // namespace NSPL
