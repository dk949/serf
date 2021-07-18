#include "arghandler.hpp"

#include "argparse.hpp"



void srf::getArgs([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    auto args = ap::ArgParse().add({"a", "b"}).add({"c", "d"}).add({"e", "f", ap::Argument::noName});


    args.printDebug();
}
