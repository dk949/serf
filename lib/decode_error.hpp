#ifndef DECODEERROR_HPP
#define DECODEERROR_HPP
#include "git2/errors.h"

const char *decodeError(git_error_code error);

#endif  // DECODEERROR_HPP
