#ifndef TASK2_LOG_H
#define TASK2_LOG_H

#include "Logger.hpp"
#include <memory>

namespace Task2 {

class Logger {
private:
    std::shared_ptr<BaseLogger> global_logger_;
    Logger();
    ~Logger() = default;
public:
    static Logger &get_instance();
    std::shared_ptr<BaseLogger> get_global_logger();
    void set_global_logger(std::shared_ptr<BaseLogger>);
};

void init_with_file_logger(const std::string &path, const Level level = Level::BASELVL);
void init_with_stdout_logger(const Level level = Level::BASELVL);
void init_with_stderr_logger(const Level level = Level::BASELVL);
void debug(const std::string &);
void info(const std::string &);
void warn(const std::string &);
void error(const std::string &);
}

#endif