#ifndef TASKS_EXCEPTIONS_H
#define TASKS_EXCEPTIONS_H

#include <stdexcept>

namespace Tasks {
class BaseException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
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

class EPollError : public BaseException {
public:
    using BaseException::BaseException;
};

class BufError : public BaseException {
public:
    using BaseException::BaseException;
};

} // namespace Tasks

#endif