#ifndef TASK2_LOGGER_H
#define TASK2_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

namespace Task2 {
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    class BaseLogger {
    protected:
        Level level_;
        virtual void log(const std::string &, const Level) = 0;

    public:
        BaseLogger();
        BaseLogger(const Level);
        virtual ~BaseLogger() noexcept;
        void debug(const std::string &);
        void info(const std::string &);
        void warn(const std::string &);
        void error(const std::string &);
        void set_level(const Level);
        Level level(void) const;
        virtual void flush() = 0;
    };

    class FileLogger : public BaseLogger {
    private:
        std::ofstream file_;
        void log(const std::string &, const Level) override;
        
    public:
        FileLogger(const std::string &);
        FileLogger(const std::string &, const Level);
        virtual void flush() override;
    };

    class StdoutLogger : public BaseLogger {
    private:
        void log(const std::string &, const Level) override;
        
    public:
        StdoutLogger();
        StdoutLogger(const Level);
        virtual void flush() override;
    };

    class StderrLogger : public BaseLogger {
    private:
        void log(const std::string &, const Level) override;
        
    public:
        StderrLogger();
        StderrLogger(const Level);
        virtual void flush() override;
    };
}


#endif