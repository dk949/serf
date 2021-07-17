#include "../argparse/argparse.hpp"

#include <catch2/catch.hpp>
#include <iostream>
/*
    TODO: test reorganisation:
        group classes with tags, not test cases.
        group methods in test cases not sections.
        group similar assertions in sections, not scopes.
        don't use scopes
    */

TEST_CASE("Argument", "[argparse][Argument]") {
    SECTION("Constructor") {
        ap::Argument a0 {"arg0"};
        CHECK_THAT(a0.argName, Catch::Matchers::Equals("arg0"));
    }
    SECTION("operator==") {
        ap::Argument a0 {"arg0"};
        ap::Argument a1 {"arg0"};
        ap::Argument a2 {"arg1"};
        CHECK(a0 == a0);
        CHECK(a0 == a1);
        CHECK(a1 == a0);
        CHECK_FALSE(a0 == a2);
    }

    SECTION("operator!=") {
        ap::Argument a0 {"arg0"};
        ap::Argument a1 {"arg0"};
        ap::Argument a2 {"arg1"};
        CHECK_FALSE(a0 != a0);
        CHECK_FALSE(a0 != a1);
        CHECK_FALSE(a1 != a0);
        CHECK(a0 != a2);
    }

    SECTION("noName") {
        CHECK(ap::Argument::noName == nullptr);
    }
}

TEST_CASE("ArgumentList", "[argparse][ArgumentList]") {
    SECTION("Constructor") {
        CHECK_NOTHROW([]() { ap::ArgumentList al0 {"arg0", "arg1", ap::Argument::noName}; }());

        {
            INFO("constructor shoudl fail because empty init-list");
            CHECK_THROWS([]() { ap::ArgumentList al0 {{}}; }());
        }

        {
            INFO("constructor shoudl fail because first arg is noName");
            CHECK_THROWS([]() { ap::ArgumentList al0 {ap::Argument::noName, "arg1", "arg2"}; }());
        }
    }

    SECTION("getArgs") {
        ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
        std::vector<ap::Argument> v0 {"arg0", "arg1", "arg2"};

        const auto test0 = al0.getArgs();
        CHECK_THAT(test0, Catch::Matchers::Equals(v0));
    }

    SECTION("operator[]") {
        ap::ArgumentList al0 {"arg0", "arg1", ap::Argument::noName};
        CHECK_THAT(al0[0].value(), Catch::Matchers::Equals("arg0"));
        CHECK(al0[2].value() == nullptr);
        CHECK_FALSE(al0[3]);
    }



    SECTION("operator==") {
        ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al1 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al2 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al3 {"arg1", "arg1", "arg2"};

        CHECK(al0 == al0);
        CHECK(al0 == al1);
        CHECK(al1 == al0);
        CHECK(al0 == al2);
        CHECK_FALSE(al0 == al3);
    }

    SECTION("operator!=") {
        ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al1 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al2 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al3 {"arg1", "arg1", "arg2"};

        CHECK_FALSE(al0 != al0);
        CHECK_FALSE(al0 != al1);
        CHECK_FALSE(al0 != al2);
        CHECK(al0 != al3);
    }


    SECTION("isSame") {
        // should be matched by al0_0, but not al0_1, al1_0 or al1_2
        std::array args0 {"serf", "arg0", "arg1", "arg2"};
        std::span<const char *> s0 {&args0.data()[1], args0.size() - 1};

        // should be matched by al1_0, but not al1_1
        std::array args1 {"serf", "arg0", "arg1", "hello"};
        std::span<const char *> s1 {&args1.data()[1], args1.size() - 1};

        // should be matched by al2_0
        std::array args2 {"serf", "arg0", "hello", "arg2", "world"};
        std::span<const char *> s2 {&args2.data()[1], args2.size() - 1};

        // should not be matched by anything, esspecially al2_0
        std::array args3 {"serf", "arg0", "arg0", "arg2", "world"};
        std::span<const char *> s3 {&args3.data()[1], args3.size() - 1};


        ap::ArgumentList al0_0 {"arg0", "arg1", "arg2"};
        ap::ArgumentList al0_1 {"arg0", "arg2", "arg2"};

        ap::ArgumentList al1_0 {"arg0", "arg1", ap::Argument::noName};
        ap::ArgumentList al1_1 {"arg0", "arg2", ap::Argument::noName};
        ap::ArgumentList al1_2 {"arg0", ap::Argument::noName, "arg2"};

        ap::ArgumentList al2_0 {"arg0", ap::Argument::noName, "arg2", ap::Argument::noName};

        {
            INFO("no data");
            auto ov0 = al0_0.isSame(s0);
            CHECK(ov0);
            CHECK(ov0.value().size() == 0);

            auto ov1 = al0_1.isSame(s0);
            CHECK_FALSE(ov1);

            auto ov2 = al1_0.isSame(s0);
            CHECK_FALSE(ov2);

            auto ov3 = al1_2.isSame(s0);
            CHECK_FALSE(ov3);
        }

        {
            INFO("single data");
            auto ov1 = al1_0.isSame(s1);
            CHECK(ov1);
            CHECK(ov1.value().size() == 1);
            CHECK_THAT(ov1.value(), Catch::Matchers::Equals(std::vector {"hello"}));

            auto ov2 = al1_1.isSame(s1);
            CHECK_FALSE(ov2);
        }

        {
            INFO("Multiple data");
            auto ov2 = al2_0.isSame(s2);
            CHECK(ov2);
            CHECK(ov2.value().size() == 2);
            CHECK_THAT(ov2.value(), Catch::Matchers::Equals(std::vector {"hello", "world"}));
        }
    }

    SECTION("size") {
        ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
        CHECK(al0.size() == 3);
    }
}


TEST_CASE("ParseResult", "[argparse][ParseResult]") {
    SECTION("Constructor") {
        INFO("regular constructor");
        CHECK_NOTHROW([]() { ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}}; }());
    }

    SECTION("is") {
        ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}};
        CHECK(pr0.is("arg0"));
        {
            INFO("is should only check 1st arg");
            CHECK_FALSE(pr0.is("arg1"));
        }
        CHECK_FALSE(pr0.is("arg2"));
    }
    SECTION("has") {
        ap::ParseResult pr0 {{"arg0", "arg1", "arg2"}, std::vector<const char *> {"hello"}};
        CHECK(pr0.has("arg1"));
        CHECK(pr0.has("arg2"));
        {
            INFO("is should not check 1st arg");
            CHECK_FALSE(pr0.has("arg0"));
        }
        CHECK_FALSE(pr0.has("arg3"));
    }

    SECTION("data") {
        ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}};
        ap::ParseResult pr1 {{"arg0", "arg1"}, std::vector<const char *> {}};
        ap::ParseResult pr2 {{"arg0", "arg1"}, std::nullopt};

        CHECK_THAT(pr0.data().value()[0], Catch::Matchers::Equals("hello"));
        CHECK(pr1.data().value().size() == 0);
        CHECK_FALSE(pr2.data());
    }
}


TEST_CASE("ArgParse", "[argparse][ArgParse][check]") {
    SECTION("Constructor") {
        CHECK_NOTHROW([]() { ap::ArgParse ap {}; }());
    }

    SECTION("add/getArgLists") {
        auto ap0 = ap::ArgParse()
                       .add({"arg0", "arg1", ap::Argument::noName})
                       .add({"arg0", "arg2", ap::Argument::noName});
        std::vector<ap::ArgumentList> test0 {{"arg0", "arg1", ap::Argument::noName},
            {"arg0", "arg2", ap::Argument::noName}};
        CHECK_THAT(ap0.getArgLists(), Catch::Matchers::Equals(test0));
    }

    SECTION("parse/noArgs") {
        // TODO: test parsing (including optional args)

        auto ap0 = ap::ArgParse()
                       .add({"arg0", "arg1", "arg2"})
                       .add({"arg0", "arg2", ap::Argument::noName});
        auto ap1 = ap::ArgParse()
                       .add({"arg0", "arg1", "arg2"})
                       .add({"arg0", ap::Argument::noName, "arg2", ap::Argument::noName});
    }
}
