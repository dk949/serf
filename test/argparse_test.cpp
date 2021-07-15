#include "../argparse/argparse.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Argument", "[argparse][Argument]") {
    SECTION("Constructor") {
        ap::Argument argument {"testName", false};
        CHECK_THAT(argument.argName, Catch::Matchers::Equals("testName", Catch::CaseSensitive::Yes));
        CHECK(argument.optional == false);
    }

    SECTION("noName") {
        CHECK(ap::Argument::noName == nullptr);
    }
}

TEST_CASE("ArgumentList", "[argparse][ArgumentList]") {
    SECTION("Constructor") {
        // regular constructor
        CHECK_NOTHROW([]() {
            ap::ArgumentList argumentList {{"arg0", false}, {"arg1", true}, {ap::Argument::noName, false}};
        }());

        // constructor shoudl fail because first arg is optional
        CHECK_THROWS([]() {
            ap::ArgumentList argumentList {{"arg0", true}, {"arg1", true}, {ap::Argument::noName, false}};
        }());

        // constructor shoudl fail because first arg is noName
        CHECK_THROWS([]() {
            ap::ArgumentList argumentList {{ap::Argument::noName, false}, {"arg1", true}, {ap::Argument::noName, false}};
        }());
    }
}


// TEST_CASE("ArgParse", "[argparse][ArgParse][check]") {
// SECTION("Constructor") {

//}
//}
