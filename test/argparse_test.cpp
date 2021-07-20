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

//     _                                         _
//    / \   _ __ __ _ _   _ _ __ ___   ___ _ __ | |_
//   / _ \ | '__/ _` | | | | '_ ` _ \ / _ \ '_ \| __|
//  / ___ \| | | (_| | |_| | | | | | |  __/ | | | |_
// /_/   \_\_|  \__, |\__,_|_| |_| |_|\___|_| |_|\__|
//              |___/

TEST_CASE("Argument::Argument(const char *)", "[argparse][Argument][Constructor]") {
    ap::Argument a0 {"arg0"};
    CHECK_THAT(static_cast<const char *>(a0), Catch::Matchers::Equals("arg0"));
}

TEST_CASE("Argument::operator==(const Argument &)", "[argparse][Argument][operator==]") {
    ap::Argument a0 {"arg0"};
    ap::Argument a1 {"arg0"};
    ap::Argument a2 {"arg1"};
    CHECK(a0 == a0);
    CHECK(a0 == a1);
    CHECK(a1 == a0);
    CHECK_FALSE(a0 == a2);
}

TEST_CASE("Argument::operator==(const char *)", "[argparse][Argument][operator==]") {
    ap::Argument a0 {"arg0"};
    const char *s0 {"arg0"};
    const char *s1 {"arg1"};
    CHECK(a0 == s0);
    CHECK(s0 == a0);
    CHECK_FALSE(a0 == s1);
}

TEST_CASE("Argument::operator!=(const Argument &)", "[argparse][Argument][operator!=]") {
    ap::Argument a0 {"arg0"};
    ap::Argument a1 {"arg0"};
    ap::Argument a2 {"arg1"};
    CHECK_FALSE(a0 != a0);
    CHECK_FALSE(a0 != a1);
    CHECK_FALSE(a1 != a0);
    CHECK(a0 != a2);
}

TEST_CASE("Argument::operator!=(const char *)", "[argparse][Argument][operator!=]") {
    ap::Argument a0 {"arg0"};
    const char *s0 {"arg0"};
    const char *s1 {"arg1"};
    CHECK_FALSE(a0 != s0);
    CHECK_FALSE(s0 != a0);
    CHECK(a0 != s1);
}


//     _                                         _   _     _     _
//    / \   _ __ __ _ _   _ _ __ ___   ___ _ __ | |_| |   (_)___| |_
//   / _ \ | '__/ _` | | | | '_ ` _ \ / _ \ '_ \| __| |   | / __| __|
//  / ___ \| | | (_| | |_| | | | | | |  __/ | | | |_| |___| \__ \ |_
// /_/   \_\_|  \__, |\__,_|_| |_| |_|\___|_| |_|\__|_____|_|___/\__|
//              |___/

TEST_CASE("ArgumentList", "[argparse][ArgumentList]") {
    SECTION("size") {
        ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
        CHECK(al0.size() == 3);
    }
}

TEST_CASE("ArgumentList::ArgumentList(std::initializer_list<Argument>)", "[argparse][ArgumentList][Constructor]") {
    SECTION("base case") {
        CHECK_NOTHROW([]() { ap::ArgumentList al0 {"arg0", "arg1", ap::Argument::noName}; }());
    }

    SECTION("empty init list") {
        CHECK_THROWS([]() { ap::ArgumentList al0 {{}}; }());
    }

    SECTION("first argument is noName") {
        CHECK_THROWS([]() { ap::ArgumentList al0 {ap::Argument::noName, "arg1", "arg2"}; }());
    }
}

TEST_CASE("ArgumentList::getArgs()", "[argparse][ArgumentList][getArgs]") {
    ap::ArgumentList al0 {"arg0", "arg1", "arg2"};

    CHECK_THAT(al0.getArgs(), Catch::Matchers::Equals(std::vector<ap::Argument> {"arg0", "arg1", "arg2"}));
}

TEST_CASE("ArgumentList::operator[](int)", "[argparse][ArgumentList][operator[]]") {
    ap::ArgumentList al0 {"arg0", "arg1", ap::Argument::noName};

    CHECK_THAT(al0[0].value(), Catch::Matchers::Equals("arg0"));
    CHECK(al0[2].value() == nullptr);
    CHECK_FALSE(al0[3]);
}

TEST_CASE("ArgumentList::operator==(const ArgumentList &)", "[argparse][ArgumentList][operator==]") {
    ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
    ap::ArgumentList al1 {"arg0", "arg1", "arg2"};
    ap::ArgumentList al2 {"arg1", "arg1", "arg2"};

    CHECK(al0 == al0);
    CHECK(al0 == al1);
    CHECK(al1 == al0);
    CHECK_FALSE(al0 == al2);
}

TEST_CASE("ArgumentList::operator!=(const ArgumentList &)", "[argparse][ArgumentList][operator!=]") {
    ap::ArgumentList al0 {"arg0", "arg1", "arg2"};
    ap::ArgumentList al1 {"arg0", "arg1", "arg2"};
    ap::ArgumentList al2 {"arg1", "arg1", "arg2"};

    CHECK_FALSE(al0 != al0);
    CHECK_FALSE(al0 != al1);
    CHECK_FALSE(al1 != al0);
    CHECK(al0 != al2);
}

TEST_CASE("ArgumentList::isSame(std::span<const char *>)", "[argparse][ArgumentList][isSame]") {
    // should be matched by al0_0, but not al0_1.
    std::array args0 {"serf", "arg0", "arg1", "arg2"};
    std::span<const char *> s0 {&args0.data()[1], args0.size() - 1};
    /*
     * Note: ideally it wouldn't match al1_0 or al1_2 either,
     * but that's impossible without having the full list of arguments and only ArgParse has that.
     * It will be possible to reject al1_0 and al1_2 in ArgParse::parse(), but not here.
     */

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

    SECTION("no data") {
        auto ov0 = al0_0.isSame(s0);
        CHECK(ov0);
        CHECK(ov0.value().size() == 0);

        auto ov1 = al0_1.isSame(s0);
        CHECK_FALSE(ov1);

        /* See note abovce
        auto ov2 = al1_0.isSame(s0);
        CHECK_FALSE(ov2);

        auto ov3 = al1_2.isSame(s0);
        CHECK_FALSE(ov3);
        */
    }

    SECTION("single data") {
        auto ov1 = al1_0.isSame(s1);
        CHECK(ov1);
        CHECK(ov1.value().size() == 1);
        CHECK_THAT(ov1.value(), Catch::Matchers::Equals(std::vector {"hello"}));

        auto ov2 = al1_1.isSame(s1);
        CHECK_FALSE(ov2);
    }

    SECTION("Multiple data") {
        auto ov2 = al2_0.isSame(s2);
        CHECK(ov2);
        CHECK(ov2.value().size() == 2);
        CHECK_THAT(ov2.value(), Catch::Matchers::Equals(std::vector {"hello", "world"}));
    }
}



//  ____                     ____                 _ _
// |  _ \ __ _ _ __ ___  ___|  _ \ ___  ___ _   _| | |_
// | |_) / _` | '__/ __|/ _ \ |_) / _ \/ __| | | | | __|
// |  __/ (_| | |  \__ \  __/  _ <  __/\__ \ |_| | | |_
// |_|   \__,_|_|  |___/\___|_| \_\___||___/\__,_|_|\__|

TEST_CASE("ParseResult::ParseResult(std::vector<const char *>, std::optional<std::vector<const char *>>)",
    "[argparse][ParseResult][Constructor]") {
    INFO("regular constructor");
    CHECK_NOTHROW([]() { ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}}; }());
}

TEST_CASE("ParseResult::is(const char *)", "[argparse][ParseResult][is]") {
    ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}};
    CHECK(pr0.is("arg0"));
    SECTION("is should only check 1st arg") {
        CHECK_FALSE(pr0.is("arg1"));
    }
    CHECK_FALSE(pr0.is("arg2"));
}

TEST_CASE("ParseResult::has(const char *)", "[argparse][ParseResult][has]") {
    ap::ParseResult pr0 {{"arg0", "arg1", "arg2"}, std::vector<const char *> {"hello"}};
    CHECK(pr0.has("arg1"));
    CHECK(pr0.has("arg2"));
    SECTION("is should not check 1st arg") {
        CHECK_FALSE(pr0.has("arg0"));
    }
    CHECK_FALSE(pr0.has("arg3"));
}


TEST_CASE("ParseResult::data()", "[argparse][ParseResult][data]") {
    ap::ParseResult pr0 {{"arg0", "arg1"}, std::vector<const char *> {"hello"}};
    ap::ParseResult pr1 {{"arg0", "arg1"}, std::vector<const char *> {}};
    ap::ParseResult pr2 {{"arg0", "arg1"}, std::nullopt};

    CHECK_THAT(pr0.data().value()[0], Catch::Matchers::Equals("hello"));
    CHECK(pr1.data().value().size() == 0);
    CHECK_FALSE(pr2.data());
}



/*     _              ____
      / \   _ __ __ _|  _ \ __ _ _ __ ___  ___
     / _ \ | '__/ _` | |_) / _` | '__/ __|/ _ \
    / ___ \| | | (_| |  __/ (_| | |  \__ \  __/
   /_/   \_\_|  \__, |_|   \__,_|_|  |___/\___|
                |___/
*/

TEST_CASE("ArgParse::ArgParse()", "[argparse][ArgParse][Constructor]") {
    CHECK_NOTHROW([]() { ap::ArgParse ap {}; }());
}


TEST_CASE("ArgParse::add(std::initializer_list<Argument>)", "[argparse][ArgParse][add]") {
    auto ap0 = ap::ArgParse()  //
                   .add({"arg0", "arg1", ap::Argument::noName})
                   .add({"arg0", "arg2", ap::Argument::noName});

    std::vector<ap::ArgumentList> test0 {{"arg0", "arg1", ap::Argument::noName}, {"arg0", "arg2", ap::Argument::noName}};
    CHECK_THAT(ap0.getArgLists(), Catch::Matchers::Equals(test0));
}
TEST_CASE("ArgParse::noArgs()", "[argparse][ArgParse][noArgs]") {
    auto ap0 = ap::ArgParse().noArgs();
    auto ap1 = ap::ArgParse();
    CHECK(ap0.canBeNull());
    CHECK_FALSE(ap1.canBeNull());
}
TEST_CASE("ArgParse::parse(std::span<const char *>)", "[argparse][ArgParse][parse]") {
    SECTION("Basic no data") {
        auto ap0 = ap::ArgParse().add({"arg0", "arg1", "arg2"});
        auto ap1 = ap::ArgParse().add({"arg0", "arg1", "arg2"}).add({"arg0", "arg1", "arg3"});
        auto ap2 = ap::ArgParse().add({"arg0", "arg1", "arg2"}).add({"arg0", "arg1", "arg3"}).noArgs();
        std::array args0 {"arg0", "arg1", "arg2"};
        std::span<const char *> sp0 {args0};

        std::array args1 {"arg0", "arg1", "arg3"};
        std::span<const char *> sp1 {args1};

        std::array<const char *, 0> args2 {};
        std::span<const char *> sp2 {args2};


        CHECK_NOTHROW(ap0.parse(sp0));
        CHECK_THROWS(ap0.parse(sp1));
        CHECK_THROWS(ap0.parse(sp2));

        CHECK_NOTHROW(ap1.parse(sp0));
        CHECK_NOTHROW(ap1.parse(sp1));
        CHECK_THROWS(ap1.parse(sp2));

        CHECK_NOTHROW(ap2.parse(sp0));
        CHECK_NOTHROW(ap2.parse(sp1));
        CHECK_NOTHROW(ap2.parse(sp2));
    }

    SECTION("Basic data") {
        auto ap0 = ap::ArgParse().add({"arg0", "arg1"});
        auto ap1 = ap::ArgParse().add({"arg0", "arg1", ap::Argument::noName});

        std::array args0 {"arg0", "arg1"};
        std::span<const char *> sp0 {args0};

        std::array args1 {"arg0", "arg1", "hello"};
        std::span<const char *> sp1 {args1};

        CHECK_NOTHROW(ap0.parse(sp0));
        CHECK_THROWS(ap0.parse(sp1));

        CHECK_THROWS(ap1.parse(sp0));
        CHECK_NOTHROW(ap1.parse(sp1));
    }
}
