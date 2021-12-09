#ifndef FSCALL_HPP
#define FSCALL_HPP

#include "status.hpp"

#include <filesystem>
#include <functional>
#include <optional>
#include <spdlog/spdlog.h>

namespace gp::fsc {

using AbsoluteT = std::filesystem::path (*)(const std::filesystem::path &, std::error_code &);
using CurrentPathT = std::filesystem::path (*)(std::error_code &);
using CreateDirT = bool (*)(const std::filesystem::path &, std::error_code &);
using IsDirT = CreateDirT;


namespace {
    void printError(std::string_view msg) {
        spdlog::critical("Error: Filesystem error: {}", msg);
    }
}  // namespace

template<typename Fn, typename... Args, typename Ret = std::invoke_result_t<Fn, Args..., std::error_code &>>
requires std::same_as<Ret, std::filesystem::path>  //
    std::optional<Ret> call(Fn fn, Args... args) {
    std::error_code err;
    const auto result = fn(args..., err);
    if (!err) {
        return result;
    }
    printError(err.message());
    return std::nullopt;
}

template<typename Fn, typename... Args, typename Ret = std::invoke_result_t<Fn, Args..., std::error_code &>>
requires std::same_as<Ret, bool>  //
st::Status call(Fn fn, Args... args) {
    std::error_code err;
    const auto result = fn(args..., err);

    if (err) {
        printError(err.message());
    } else if (result) {
        return st::Ok;
    }
    return st::Err(st::Status::FS_ERROR);
}
}  // namespace gp::fsc

#endif  // FSCALL_HPP
