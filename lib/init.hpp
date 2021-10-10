#ifndef INIT_HPP
#define INIT_HPP
#include "fs.hpp"
#include "status.hpp"

#include <filesystem>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>


// TODO: use boost::outcome<>

namespace gp {
st::Status init(std::optional<std::vector<std::string>> path) {
    fs::PathT workingDir;
    if (path) {
        workingDir = fs::getAbsPath(std::string_view {(*path)[0]});
    } else {
        workingDir = fs::getCWD();
    }

    if (!workingDir) {
        return Err(st::Status::FS_ERROR);
    }


    fs::createDir(*workingDir);
    workingDir->append("serf_packages.json");
    fs::createFile(*workingDir);
    fs::createDir(workingDir->parent_path().append("serf_store"));

    return st::Ok;
}


}  // namespace gp

#endif  // INIT_HPP
