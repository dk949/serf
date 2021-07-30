#ifndef REPO_HPP
#define REPO_HPP

#include "common_types.hpp"

#include <filesystem>
#include <git2.h>
#include <optional>
#include <vector>

namespace gp {
class Repo {
public:
    using OptRepo_t = std::optional<Repo>;

private:
    git_repository *m_repo;
    Path_t m_path;
    URL_t m_url;
    mutable std::vector<git_buf> m_buffers;

private:
    explicit Repo(git_repository *repo,
        std::optional<Path_t> path = std::nullopt,
        std::optional<URL_t> url = std::nullopt,
        std::optional<git_buf> buffer = std::nullopt);

public:
    ~Repo();



    // static
    // TODO: make an overload for all factories with options

    static OptRepo_t init(const Path_t &path, bool isBare = false);

    // TODO: progress
    static OptRepo_t clone(const URL_t &url, const Path_t &path);

    static OptRepo_t open(const Path_t &path);

    static OptRepo_t openUnknownRoot(const Path_t &path);
};
}  // namespace gp

#endif  // REPO_HPP
