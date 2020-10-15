#ifndef HW_EXCEPTIONS_H
#define HW_EXCEPTIONS_H

#include <stdexcept>

namespace Task1 {
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

} // namespace Task1

#endif