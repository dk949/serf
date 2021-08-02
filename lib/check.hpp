#ifndef CHECK_HPP
#define CHECK_HPP
#include "git2/errors.h"
#include "exceptions.hpp"
#define gpCall(X)                                 \
    if (!check(static_cast<git_error_code>((X)))) \
    return std::nullopt

namespace gp {
bool check(git_error_code error);
}

#endif  // CHECK_HPP
