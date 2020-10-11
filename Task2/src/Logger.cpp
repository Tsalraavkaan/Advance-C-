#include "Logger.hpp"

namespace Task2 {
    BaseLogger::BaseLogger() : level_{Level::DEBUG} {}

    BaseLogger::BaseLogger(const Level level) : level_{level} {}

    BaseLogger::~BaseLogger() {}

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

    Level BaseLogger::level(void) const {
        return level_;
    }

    FileLogger::FileLogger(const std::string &path, const Level level) :
            BaseLogger(level), file_(path, std::ios::app) {}

    FileLogger::FileLogger(const std::string &path) : BaseLogger(Level::DEBUG), file_(path, std::ios::app) {}

    void FileLogger::log(const std::string &message, const Level lvl) {
        if (level() <= lvl) {
            file_ << message << std::endl;
        }
    }

    void FileLogger::flush(void) {
        file_.flush();
    }

    StdoutLogger::StdoutLogger() : BaseLogger() {}

    StdoutLogger::StdoutLogger(const Level level = Level::DEBUG) : BaseLogger(level) {}

    void StdoutLogger::flush(void) {
        std::flush(std::cout);
    }

    void StdoutLogger::log(const std::string &message, const Level lvl) {
        if (level() <= lvl) {
            std::cout << message << std::endl;
        }
    }

    StderrLogger::StderrLogger() : BaseLogger() {}

    StderrLogger::StderrLogger(const Level level = Level::DEBUG) : BaseLogger(level) {}

    void StderrLogger::flush(void) {
        std::flush(std::cout);
    }

    void StderrLogger::log(const std::string &message, const Level lvl) {
        if (level() <= lvl) {
            std::cerr << message << std::endl;
        }
    }

}