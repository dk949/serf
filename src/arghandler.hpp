#ifndef ARGHANDLER_HPP
#define ARGHANDLER_HPP

#include <span>

namespace srf{
    void getArgs(std::span<const char *> args);
}

#endif // ARGHANDLER_HPP
