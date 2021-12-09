#include "arghandler.hpp"  // for getArgs
#include "argparse.hpp"    // for getArgsSpan
#include "gitpac.hpp"

#include <memory>           // for allocator
#include <spdlog/spdlog.h>  // for set_pattern



int main(int argc, const char **argv) {
    spdlog::set_pattern("%^%v%$");

    const auto parsedOpt = srf::getParsed(ap::getArgsSpan(argc, argv));
    if (!parsedOpt) {
        spdlog::critical("Could not parse");
        std::exit(-1);
    }
    const auto parsed = *parsedOpt;

    if (parsed.is()) {
        spdlog::critical("nothing passed in");
        std::exit(-1);
    } else if (parsed.is("init")) {
        if (const auto status = gp::init(parsed.data()); status != st::Ok) {
            spdlog::critical("Could not get init path");
            std::exit(status.val);
        }
    } else if (parsed.is("clone")) {
        if (const auto status = gp::clone(parsed.data()); status != st::Ok) {
            spdlog::critical("Could not clone repo");
            std::exit(status.val);
        }
    } else if (parsed.is("delete")) {
        const auto data = parsed.data().value();
        spdlog::info("delete. data = {}", data[0]);
    } else if (parsed.is("checkout")) {
        const auto data = parsed.data().value();
        spdlog::info("checkout. data = {}", data[0]);
    } else if (parsed.is("update")) {
        if (const auto data = parsed.data()) {
            spdlog::info("udpate. data = {}", (*data)[0]);
        } else {
            spdlog::info("update with no data");
        }
    } else if (parsed.is("latest")) {
        const auto data = parsed.data().value();
        spdlog::info("latest. data = {}", data[0]);
    } else if (parsed.is("pull")) {
        if (const auto data = parsed.data()) {
            spdlog::info("pull. data = {}", (*data)[0]);
        } else {
            spdlog::info("pull with no data");
        }
    } else if (parsed.is("setup")) {
        spdlog::info("setup with no data");
    }

    return 0;
}
