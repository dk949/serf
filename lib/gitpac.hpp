#ifndef core_hpp
#define core_hpp
#include "git_exception.hpp"
#include "repo.hpp"

#include <git2.h>



namespace gp {
class Git {
public:
    // ctors and dtor
    Git();
    ~Git();
};



}  // namespace gp

#endif  // core_hpp
