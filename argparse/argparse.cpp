#include "argparse.hpp"

#include<ctre.hpp>
#include <spdlog/spdlog.h>

void ap::foo() {
    const auto sv = "hello";
    const bool match = ctre::match<"h.*">(sv);
    spdlog::info("It's{} a match",!match ? " not":"" );
}
