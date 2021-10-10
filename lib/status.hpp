#ifndef STATUS_HPP
#define STATUS_HPP

#include <compare>


namespace st {
struct Status {
    char val;
    operator bool() {
        return !val;
    }
    enum StatusCode : char {
        INT_ERROR = -1,
        OK,
        FS_ERROR,
        NET_ERROR,
    };
    std::partial_ordering operator<=>(const Status &) const = default;
};

constexpr Status Ok = Status {Status::OK};

constexpr Status Err(Status::StatusCode status) {
    return Status {status};
}

}  // namespace st


#endif  // STATUS_HPP
