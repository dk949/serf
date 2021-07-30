#ifndef ARGHANDLER_HPP
#define ARGHANDLER_HPP

#include <span>
namespace ap {
// forward declaring to avoid includes
class ParseResult;
}  // namespace ap

namespace srf {
ap::ParseResult getParsed(std::span<const char *> args);
}

#endif  // ARGHANDLER_HPP
