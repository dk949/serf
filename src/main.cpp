#include "arghandler.hpp"
#include "gitpac.hpp"

#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, const char **argv) {
    spdlog::set_pattern("[%l]: %v");

    srf::getArgs(argc, argv);

    return 0;
}
