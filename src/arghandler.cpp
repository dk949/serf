#include "arghandler.hpp"

#include "argparse.hpp"


struct A {
    int a;
    const char *b;
};

void srf::getArgs([[maybe_unused]] int argc, [[maybe_unused]] const char **argv) {
    auto args =
        ap::ArgParse()
        .add({{"a", false}, {"b", true}})
        .add({{"c", false}, {"d", true}})
        .add({{"e", false}, {"f", true}, {nullptr, false}});


    args.printDebug();
}
