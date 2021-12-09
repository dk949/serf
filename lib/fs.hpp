#ifndef FS_HPP
#define FS_HPP
#include "fscall.hpp"
#include "status.hpp"

#include <filesystem>
#include <fstream>
#include <optional>
#include <spdlog/spdlog.h>
#include <string_view>

namespace gp::fs {


std::string_view getFileStatus(const std::ofstream &f) {
    return f.bad()  ? "Non-recovarable error" :
           f.fail() ? "Recoverable error" :
           f.eof()  ? "Unexpected EOF" :
                      "Unknown error type";
}
using PathT = std::optional<std::filesystem::path>;

PathT getAbsPath(std::string_view path) {
    return fsc::call<fsc::AbsoluteT>(std::filesystem::absolute, path);
}

PathT getAbsPath(const std::filesystem::path &path) {
    return getAbsPath(std::string_view {path.string()});
}

PathT getCWD() {
    return fsc::call<fsc::CurrentPathT>(std::filesystem::current_path);
}

st::Status createDir(const std::filesystem::path &path) {
    return fsc::call<fsc::CreateDirT>(std::filesystem::create_directory, path);
}

st::Status createFile(const std::filesystem::path &path) {
    std::ofstream f {path};
    if (!f) {
        spdlog::critical(  //
            "Error: Could not write to file {}. {}",
            path.string(),
            getFileStatus(f));
        return st::Err(st::Status::FS_ERROR);
    }

    f << R"({
        "hello": "file"
    })";
    return st::Ok;
}

PathT getSerfRoot(std::filesystem::path path) {
    const auto root = path.root_directory();  // Apparantly this one literally cannot fail

    if (!fsc::call<fsc::IsDirT>(std::filesystem::is_directory, path)) {
        path = path.parent_path();
    }

    while (path != root) {
        for (const auto &elem : std::filesystem::directory_iterator(path)) {
            if (elem.is_regular_file() && elem.path().filename() == "serf_packages.json") {
                spdlog::info("path = {}, root = {}, path == root = {}", path.string(), root.string(), path == root);
                return path;
            }
        }
        path = path.parent_path();
    }
    return std::nullopt;
}

}  // namespace gp::fs

#endif  // FS_HPP
