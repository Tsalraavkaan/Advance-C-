#ifndef PROJECT_EXCEPTIONS
#define PROJECT_EXCEPTIONS

#include <stdexcept>

namespace Project {
namespace Except {

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

class EPollError : public BaseException {
public:
    using BaseException::BaseException;
};

class SemError : public BaseException {
public:
    using BaseException::BaseException;
};

class KeyError : public BaseException {
public:
    using BaseException::BaseException;
};

class MapError : public BaseException {
public:
    using BaseException::BaseException;
};

class BufError : public BaseException {
public:
    using BaseException::BaseException;
};

} // namespace Except
} // namespace Project

#endif