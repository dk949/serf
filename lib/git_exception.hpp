#ifndef GIT_EXCEPTION_HPP
#define GIT_EXCEPTION_HPP
#include "check.hpp"
#include "git2.h"

#include <exception>
#include <fmt/format.h>

namespace gp {
class GitException : std::exception {
private:
    std::string m_message;

public:
    GitException(git_error_code error, const git_error *e);
    GitException(git_error_code error, const git_error *e, const char *userMessage);
    GitException(git_error_code error, git_error_t klass, const char *message);
    GitException(git_error_code error, git_error_t klass, const char *message, const char *userMessage);


    const char *what() const noexcept override {
        return m_message.c_str();
    }
};

}  // namespace gp

#endif  // GIT_EXCEPTION_HPP
