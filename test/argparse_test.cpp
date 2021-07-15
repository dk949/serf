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
            ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {ap::Argument::noName, false}};
        }());

        // constructor shoudl fail because empty init-list
        CHECK_THROWS([]() { ap::ArgumentList al0 {{}}; }());

        // constructor shoudl fail because first arg is optional
        CHECK_THROWS([]() { ap::ArgumentList al0 {{"arg0", true}, {"arg1", false}, {"arg2", false}}; }());

        // constructor shoudl fail because first arg is noName
        CHECK_THROWS([]() {
            ap::ArgumentList al0 {{ap::Argument::noName, false}, {"arg1", false}, {"arg2", false}};
        }());
    }

    SECTION("getArgs") {
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        std::vector<ap::Argument> v0{{"arg0", false}, {"arg1", false}, {"arg2", false}};

        const auto test0 = al0.getArgs();
        CHECK_THAT(test0, Catch::Matchers::Equals(v0));
    }

    SECTION("size") {
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};
        CHECK(al0.size() == 3);
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

    SECTION("operator[]") {
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {ap::Argument::noName, false}};
        CHECK_THAT(al0[0].value(), Catch::Matchers::Equals("arg0"));
        CHECK(al0[2].value() == nullptr);
        CHECK_FALSE(al0[3]);
    }
}


// TEST_CASE("ArgParse", "[argparse][ArgParse][check]") {
// SECTION("Constructor") {

//}
//}
