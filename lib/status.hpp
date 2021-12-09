#ifndef STATUS_HPP
#define STATUS_HPP

#include <compare>


namespace st {
struct Status {
    char val;
    constexpr operator bool() const {
        return !val;
    }
    enum StatusCode : char {
        INT_ERROR = -1,  // Internal error, a bug within serf
        OK,              // All good
        FS_ERROR,        // Error returned by the file system API
        NET_ERROR,       // Could not connect to the network or a specified domain
        SERF_ERROR,      // User error
    };
    std::partial_ordering operator<=>(const Status &) const = default;
};

constexpr Status Ok = Status {Status::OK};

constexpr Status Err(Status::StatusCode status) {
    return Status {status};
}

}  // namespace st


#endif  // STATUS_HPP
