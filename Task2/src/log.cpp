#include "log.hpp"

namespace Task2 {
    Logger::Logger() : global_logger_(std::unique_ptr<StdoutLogger>(new StdoutLogger())) {}

    Logger &Logger::get_instance() {
        static Logger log_instance;
        return log_instance;
    }

    BaseLogger &Logger::get_global_logger() {
        return *global_logger_;
    }

    void Logger::set_global_logger(std::unique_ptr<BaseLogger> logger) {
        if (logger != nullptr) {
            global_logger_ = std::move(logger);
        }
    }

    std::unique_ptr<FileLogger> init_with_file_logger(const std::string &path, const Level level) {
        return std::make_unique<FileLogger>(path, level);
    }

    std::unique_ptr<StdoutLogger> init_with_stdout_logger(const Level level) {
        return std::make_unique<StdoutLogger>(level);
    }

    std::unique_ptr<StderrLogger> init_with_stderr_logger(const Level level) {
        return std::make_unique<StderrLogger>(level);
    }

    void debug(const std::string &message) {
        Logger::get_instance().get_global_logger().debug(message);
    }

    void info(const std::string &message) {
        Logger::get_instance().get_global_logger().info(message);
    }

    void warn(const std::string &message) {
        Logger::get_instance().get_global_logger().warn(message);
    }

    void error(const std::string &message) {
        Logger::get_instance().get_global_logger().error(message);
    }

}