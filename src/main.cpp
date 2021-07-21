#include "arghandler.hpp"  // for getArgs
#include "argparse.hpp"    // for getArgsSpan

#include <memory>           // for allocator
#include <spdlog/spdlog.h>  // for set_pattern



int main(int argc, const char **argv) {
    spdlog::set_pattern("[%l]: %v");


    srf::getArgs(ap::getArgsSpan(argc, argv));


    return 0;
}
