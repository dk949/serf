#ifndef FS_HPP
#define FS_HPP
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
    std::error_code err;
    const auto absPath = std::filesystem::absolute(path, err);
    if (!err) {
        return absPath;
    }
    spdlog::critical(  //
        "Error: {}: Could not get asolute valie fo directory {}",
        err.message(),
        path);
    return std::nullopt;
}

PathT getAbsPath(const std::filesystem::path &path) {
    return getAbsPath(std::string_view {path.string()});
}

PathT getCWD() {
    std::error_code err;
    const auto currPath = std::filesystem::current_path();
    if (!err) {
        return currPath;
    }
    spdlog::critical(  //
        "Error: {}: Could not get Could not get current directory",
        err.message());
    return std::nullopt;
}

st::Status createDir(const std::filesystem::path &path) {
    std::error_code err;
    std::filesystem::create_directory(path, err);
    if (!err) {
        return st::Ok;
    }

    spdlog::critical(  //
        "Error: {}: Could not create directory {}",
        err.message(),
        path.string());
    return st::Err(st::Status::FS_ERROR);
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

}  // namespace gp::fs

#endif  // FS_HPP
