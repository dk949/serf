#include "gitpac.hpp"

gp::Git::Git() {
    git_libgit2_init();
}


gp::Git::~Git() {
    git_libgit2_shutdown();
}

