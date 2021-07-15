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

    SECTION("getArgs") {
        ap::ArgumentList argumentList {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        CHECK(argumentList.size() == 3);
    }


    SECTION("operator==") {
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        ap::ArgumentList al1 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        ap::ArgumentList al2 {{"arg0", false}, {"arg1", true}, {"arg2", true}};
        ap::ArgumentList al3 {{"arg1", false}, {"arg1", true}, {"arg2", true}};

        CHECK(al0 == al1);
        CHECK(al0 == al2);
        CHECK_FALSE(al0 == al3);
    }

    SECTION("operator!=") {
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        ap::ArgumentList al1 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        ap::ArgumentList al2 {{"arg0", false}, {"arg1", true}, {"arg2", true}};
        ap::ArgumentList al3 {{"arg1", false}, {"arg1", true}, {"arg2", true}};

        CHECK_FALSE(al0 != al1);
        CHECK_FALSE(al0 != al2);
        CHECK(al0 != al3);
    }
}


// TEST_CASE("ArgParse", "[argparse][ArgParse][check]") {
// SECTION("Constructor") {

//}
//}
