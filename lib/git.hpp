#ifndef GIT_HPP
#define GIT_HPP
#include "decode_error.hpp"
#include "decode_klass.hpp"
#include "status.hpp"
#include "url.hpp"

#include <git2.h>
#include <spdlog/spdlog.h>
#include <vector>

namespace gp {
class Git {
public:
    Git() {
        // Technically this can return an error, but it probably wont
        const auto err = git_error_code(git_libgit2_init());
        if (err < 0) {
            spdlog::critical("Error: {}: Could not initialise libgit2", decodeError(err));
        }
    }
    Git(const Git &) = delete;
    Git(Git &&) = delete;
    Git &operator=(const Git &) = delete;
    Git &operator=(Git &&) = delete;
    ~Git() {
        git_libgit2_shutdown();
    }

    st::Status clone(const URL &url, std::string_view path) {
        spdlog::info("Called");
        git_repository *repo = NULL;
        const auto err = git_error_code(git_clone(&repo, url.str().c_str(), path.data(), NULL));
        if (err) {
            const auto lastErr = git_error_last();
            spdlog::critical(  //
                "Error: ({}/{}): {}: Could not clone {} to {}",
                decodeError(err),
                decodeKlass(git_error_t(lastErr->klass)),
                lastErr->message,
                url.str(),
                path);
            // will need to return propper erro here
            return st::Err(st::Status::INT_ERROR);
        }
        git_repository_free(repo);
        return st::Ok;
    }
};
}  // namespace gp

#endif  // GIT_HPP
