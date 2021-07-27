#include "git_exception.hpp"


gp::GitException::GitException(int error,  //
    const git_error *e):
        std::exception(),                   //
        m_message(fmt::format("{}/{}: {}",  //
            error,
            e->klass,
            e->message)) {}

gp::GitException::GitException(int error,  //
    const git_error *e,
    const char *userMessage):
        std::exception(),                         //
        m_message(fmt::format("{}/{}: {} // {}",  //
            error,
            e->klass,
            e->message,
            userMessage)) {}

gp::GitException::GitException(int error,  //
    int klass,
    const char *message):
        std::exception(),                   //
        m_message(fmt::format("{}/{}: {}",  //
            error,
            klass,
            message)) {}

gp::GitException::GitException(int error,  //
    int klass,
    const char *message,
    const char *userMessage):
        std::exception(),                         //
        m_message(fmt::format("{}/{}: {} // {}",  //
            error,
            klass,
            message,
            userMessage)) {}
