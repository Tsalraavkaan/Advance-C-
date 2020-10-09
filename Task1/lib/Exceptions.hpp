#ifndef HW_EXCEPTIONS_H
#define HW_EXCEPTIONS_H

#include <exception>
#include <string>

namespace Task1 {

    class BaseException : public std::exception  {
    private:
        std::string info_;

    public:
        BaseException(const std::string &);
        const char *what() const noexcept override;
    };

    class PipeError : public BaseException  {
    public:
        PipeError(const std::string &);
    };

    class ProcessError : public BaseException  {
    public:
        ProcessError(const std::string &);
    };

    class DescriptorError : public BaseException 
    {
    public:
        DescriptorError(const std::string &);
    };

    class ReadingError : public BaseException 
    {
    public:
        ReadingError(const std::string &);
    };

    class WritingError : public BaseException 
    {
    public:
        WritingError(const std::string &);
    };

}

#endif