#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP
#include <filesystem>


namespace gp {
using Path_t = std::filesystem::path;
using URL_t = const char *;
using Hash_t = const char *;

}  // namespace gp

#endif  // COMMON_TYPES_HPP
