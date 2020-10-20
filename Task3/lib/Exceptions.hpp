#ifndef HW_EXCEPTIONS_H
#define HW_EXCEPTIONS_H

#include <stdexcept>

namespace Tasks {
class BaseException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PipeError : public BaseException {
public:
    using BaseException::BaseException;
};

class ProcessError : public BaseException {
public:
    using BaseException::BaseException;
};

class DescriptorError : public BaseException {
public:
    using BaseException::BaseException;
};

class ReadingError : public BaseException {
public:
    using BaseException::BaseException;
};

class WritingError : public BaseException {
public:
    using BaseException::BaseException;
};

class TimeoutError : public BaseException {
public:
    using BaseException::BaseException;
};

class ConnectionError : public BaseException {
public:
    using BaseException::BaseException;
};

} // namespace Tasks

#endif