#include "log.hpp"

namespace Task2 {

Logger::Logger(std::unique_ptr<BaseLogger> logger) : global_logger_(std::move(logger)) {}

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

void init_with_file_logger(const std::string &path, const Level level) {
    Logger::get_instance().set_global_logger(std::make_unique<FileLogger>(path, level));
}

void init_with_stdout_logger(const Level level) {
    Logger::get_instance().set_global_logger(std::make_unique<StdoutLogger>(level));
}

void init_with_stderr_logger(const Level level) {
    Logger::get_instance().set_global_logger(std::make_unique<StderrLogger>(level));
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

} //namespace Task2