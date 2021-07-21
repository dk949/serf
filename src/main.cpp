#include "arghandler.hpp"
#include "argparse.hpp"
#include "gitpac.hpp"

#include <iostream>
#include <span>
#include <spdlog/spdlog.h>

int main(int argc, const char **argv) {
    spdlog::set_pattern("[%l]: %v");


    srf::getArgs(ap::getArgsSpan(argc, argv));


    return 0;
}
