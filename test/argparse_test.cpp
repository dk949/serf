#include "../argparse/argparse.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Argument", "[argparse][Argument][check]") {
    SECTION("Constructor") {
        ap::Argument argument {"testName", false};
        CHECK_THAT(argument.argName, Catch::Matchers::Equals("testName", Catch::CaseSensitive::Yes));
        CHECK(argument.optional == false);
    }

    SECTION("noName") {
        CHECK(ap::Argument::noName == nullptr);
    }
}
