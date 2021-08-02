#include "arghandler.hpp"  // for getArgs
#include "argparse.hpp"    // for getArgsSpan

#include <memory>           // for allocator
#include <spdlog/spdlog.h>  // for set_pattern



int main(int argc, const char **argv) {
    spdlog::set_pattern("[%l]: %v");

    const auto parsed = srf::getParsed(ap::getArgsSpan(argc, argv));

    if (parsed.is()) {
        spdlog::info("nothing passed in");
    } else if (parsed.is("init")) {
        if (const auto data = parsed.data()) {
            spdlog::info("init. data = {}", (*data)[0]);
        } else {
            spdlog::info("init with no data");
        }
    } else if (parsed.is("clone")) {
        const auto data = parsed.data().value();
        if (data.size() == 1) {
            spdlog::info("clone with 1 data. data = {}", data[0]);
        } else if (data.size() == 2) {
            spdlog::info("clone with 2 data. data1 = {}, data2 = {}", data[0], data[1]);
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
