#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "common_types.hpp"

#include <optional>
namespace gp {
struct Package {
    std::optional<const char *> branch;
    std::optional<Hash_t> hash;
    Path_t path;
    URL_t url;
    int urlhash;
};
}  // namespace gp

#endif  // PACKAGE_HPP
