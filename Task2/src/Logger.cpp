#include "Logger.hpp"

namespace Task2 {

BaseLogger::BaseLogger(const Level level, std::basic_ostream<char> *stream)
        : level_{level}, stream_{stream} {}

void BaseLogger::log(const std::string &message, const Level lvl) {
    if (level_ <= lvl) {
        *stream_ << message << std::endl;
    }
}

void BaseLogger::flush(void) {
    stream_->flush();
}

void BaseLogger::debug(const std::string &message) {
    log(message, Level::DEBUG);
}

void BaseLogger::info(const std::string &message) {
    log(message, Level::INFO);
}

void BaseLogger::warn(const std::string &message) {
    log(message, Level::WARN);
}

void BaseLogger::error(const std::string &message) {
    log(message, Level::ERROR);
}

void BaseLogger::set_level(const Level level) {
    level_ = level;
}

FileLogger::FileLogger(const std::string &path, const Level level) :
        file_{std::ofstream(path, std::ios::app)}, BaseLogger(level, &file_) {}

FileLogger::~FileLogger() {
    flush();
}

StdoutLogger::StdoutLogger(const Level level) : BaseLogger(level, &std::cout) {}

StderrLogger::StderrLogger(const Level level) : BaseLogger(level, &std::cerr) {}

} //namespace Task2