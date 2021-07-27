#include "repo.hpp"


namespace fs = std::filesystem;

#include "check.hpp"

gp::Repo::Repo(git_repository *repo,  //
    std::optional<Path_t> path,
    std::optional<URL_t> url,
    std::optional<git_buf> buffer):
        m_repo(repo),  //
        m_path(path.value_or(Path_t {})),
        m_url(url.value_or(URL_t {})) {
    if (buffer) {
        m_buffers.push_back(*buffer);
    }
}


gp::Repo::~Repo() {
    std::for_each(std::begin(m_buffers), std::end(m_buffers), [](git_buf &buf) {  //
        git_buf_free(&buf);
    });
    git_repository_free(m_repo);
}



gp::Repo::OptRepo_t gp::Repo::init(const Path_t &path, bool isBare) {
    git_repository *repo;
    gpCall(git_repository_init(&repo, path.c_str(), isBare));
    return Repo(repo, path);
}


gp::Repo::OptRepo_t gp::Repo::clone(const URL_t &url, const Path_t &path) {
    git_repository *repo;
    gpCall(git_clone(&repo, url, path.c_str(), nullptr));
    return Repo(repo, path, url);
}

gp::Repo::OptRepo_t gp::Repo::open(const Path_t &path) {
    git_repository *repo;
    gpCall(git_repository_open(&repo, path.c_str()));
    return Repo(repo, path);
}

gp::Repo::OptRepo_t gp::Repo::openUnknownRoot(const Path_t &path) {
    git_buf root;
    git_repository *repo;

    gpCall(git_repository_discover(&root, path.c_str(), 0, nullptr));
    if (root.ptr) {
        gpCall(git_repository_open(&repo, root.ptr));
        return Repo(repo, Path_t(root.ptr), std::nullopt, root);
    }
    git_buf_free(&root);
    return std::nullopt;
}
