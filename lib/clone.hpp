#ifndef CLONE_HPP
#define CLONE_HPP

#include "fs.hpp"
#include "git.hpp"
#include "status.hpp"
#include "url.hpp"

#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>
#include <vector>


namespace gp {

st::Status clone(std::optional<std::vector<std::string>> data) {
    if (!data || data->empty()) {
        spdlog::critical("Unrecovarable internal error: No clone data");
        return st::Err(st::Status::INT_ERROR);
    }
    const auto url = URL::makeUrl((*data)[0]);
    if (!url) {
        spdlog::error("Error: Invalid url {}", (*data)[0]);
        return st::Err(st::Status::SERF_ERROR);
    }

    fs::PathT workingDir;
    if (data->size() > 1) {
        workingDir = fs::getAbsPath(std::string_view {(*data)[1]});
    } else {
        workingDir = fs::getCWD();
    }
    if (!workingDir) {
        return Err(st::Status::FS_ERROR);
    }

    auto serfRoot = fs::getSerfRoot(*workingDir);
    if (!serfRoot) {
        spdlog::error("serf clone can only be used in a serf directory");
        return st::Err(st::Status::SERF_ERROR);
    };

    spdlog::info("workingDir = {}", workingDir->string());

    Git git;
    // FIXME: probably will have an issue with utf8 vs utf16
    if (const auto status = git.clone(*url,
            std::string_view {(*serfRoot).append("serf_store").append("HASH_WILL_BE_HERE_IN_THE_FUTURE").string()});
        status != st::Ok) {
        return status;
    }

    return st::Ok;
}


}  // namespace gp

#endif  // CLONE_HPP
