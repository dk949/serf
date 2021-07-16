#include "../argparse/argparse.hpp"

#include <catch2/catch.hpp>
#include <iostream>

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
        std::vector<ap::Argument> v0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};

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

    SECTION("isSame") {
        // no data
        std::array args0 {"serf", "arg0", "arg1", "arg2"};
        std::span<const char *> s0 {&args0.data()[1], args0.size() - 1};

        // single data
        std::array args1 {"serf", "arg0", "arg1", "hello"};
        std::span<const char *> s1 {&args1.data()[1], args1.size() - 1};

        // multiple data
        std::array args2 {"serf","arg0", "hello", "arg2", "world"};
        std::span<const char *> s2 {&args2.data()[1], args2.size() - 1};


        // seccess no data
        ap::ArgumentList al0 {{"arg0", false}, {"arg1", false}, {"arg2", false}};

        // seccess single data
        ap::ArgumentList al1_0 {{"arg0", false}, {"arg1", false}, {ap::Argument::noName, false}};

        // seccess single data optional param
        ap::ArgumentList al1_1 {{"arg0", false}, {"arg1", true}, {ap::Argument::noName, false}};

        // fail single data
        ap::ArgumentList al1_2 {{"arg0", false}, {"arg0", true}, {ap::Argument::noName, false}};

        // Multipla data
        ap::ArgumentList al2 {{"arg0", false}, {ap::Argument::noName, false}, {"arg2", true}, {ap::Argument::noName, false}};


        // No data
        auto ov0 = al0.isSame(s0);
        CHECK(ov0);
        CHECK(ov0.value().size() == 0);
        //CHECK_THAT(ov0.value()[0], Catch::Matchers::Equals(""));

        // single data
        auto ov1_0 = al1_0.isSame(s1);
        CHECK(ov1_0);
        CHECK(ov1_0.value().size() == 1);
        CHECK_THAT(ov1_0.value()[0], Catch::Matchers::Equals("hello"));

        auto ov1_1 = al1_1.isSame(s1);
        CHECK(ov1_1);
        CHECK(ov1_1.value().size() == 1);
        CHECK_THAT(ov1_1.value()[0], Catch::Matchers::Equals("hello"));

        auto ov1_2 = al1_2.isSame(s1);
        CHECK_FALSE(ov1_2);

        // Multiple data
        auto ov2 = al2.isSame(s2);
        CHECK(ov2);
        CHECK(ov2.value().size() == 2);
        CHECK_THAT(ov2.value()[0], Catch::Matchers::Equals("hello"));
        CHECK_THAT(ov2.value()[1], Catch::Matchers::Equals("world"));
    }
}


// TEST_CASE("ArgParse", "[argparse][ArgParse][check]") {
// SECTION("Constructor") {

//}
//}
