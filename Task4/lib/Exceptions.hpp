#ifndef TASKS_EXCEPTIONS_H
#define TASKS_EXCEPTIONS_H

#include <stdexcept>

namespace Tasks {
class BaseException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class KeyError : public BaseException {
public:
    using BaseException::BaseException;
};

class MapError : public BaseException {
public:
    using BaseException::BaseException;
};

} // namespace Tasks

#endif