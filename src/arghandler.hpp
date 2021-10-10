#ifndef ARGHANDLER_HPP
#define ARGHANDLER_HPP

#include <span>
#include <optional>
namespace ap {
// forward declaring to avoid includes
class ParseResult;
}  // namespace ap

namespace srf {
    std::optional<ap::ParseResult> getParsed(std::span<const char *> args);
}

#endif  // ARGHANDLER_HPP
