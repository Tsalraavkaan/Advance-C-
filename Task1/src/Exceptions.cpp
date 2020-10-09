#include "Exceptions.hpp"

namespace Task1 {

    BaseException::BaseException(const std::string &info) : info_{info} {}

    const char *BaseException::what() const noexcept {
        return info_.c_str();
    }

    PipeError::PipeError(const std::string &info) : BaseException{info} {}

    ProcessError::ProcessError(const std::string &info) : BaseException{info} {}

    DescriptorError::DescriptorError(const std::string &info) : BaseException{info} {}

    ReadingError::ReadingError(const std::string &info) : BaseException{info} {}

    WritingError::WritingError(const std::string &info) : BaseException{info} {}

} 