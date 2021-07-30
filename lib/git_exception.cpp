#include "git_exception.hpp"

#include "decode_error.hpp"
#include "decode_klass.hpp"


gp::GitException::GitException(git_error_code error,  //
    const git_error *e):
        std::exception(),                   //
        m_message(fmt::format("{}/{}: {}",  //
            decodeError(error),
            decodeKlass(static_cast<git_error_t>(e->klass)),
            e->message)) {}

gp::GitException::GitException(git_error_code error,  //
    const git_error *e,
    const char *userMessage):
        std::exception(),                         //
        m_message(fmt::format("{}/{}: {} // {}",  //
            decodeError(error),
            decodeKlass(static_cast<git_error_t>(e->klass)),
            e->message,
            userMessage)) {}

gp::GitException::GitException(git_error_code error,  //
    git_error_t klass,
    const char *message):
        std::exception(),                   //
        m_message(fmt::format("{}/{}: {}",  //
            decodeError(error),
            decodeKlass(klass),
            message)) {}

gp::GitException::GitException(git_error_code error,  //
    git_error_t klass,
    const char *message,
    const char *userMessage):
        std::exception(),                         //
        m_message(fmt::format("{}/{}: {} // {}",  //
            decodeError(error),
            decodeKlass(klass),
            message,
            userMessage)) {}
