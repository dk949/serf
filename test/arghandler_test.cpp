#include "../argparse/argparse.hpp"  // for getArgsSpan
#include "../src/arghandler.hpp"     // for getArgs

#include <array>             // for array
#include <catch2/catch.hpp>  // for SourceLineInfo, Section, operato...
#include <memory>            // for allocator

TEST_CASE("init", "[arghandler]") {
    //### `serf init`
    //### `serf init [DIR_NAME]`

    SECTION("serf init (nothrow)") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());


        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf init dir (nothrow)") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf init dir arg (throws, too many args") {
        auto argv = std::array {"serf", "init", "dir", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}


TEST_CASE("clone", "[arghandler]") {
    //    ### `serf clone [REPO_URL] [PATH]`
    //    ### `serf clone [REPO_URL]`
    SECTION("serf clone https://github.com/dk949/serf_testrepo.git (nothrow)") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git (nothrow)") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf clone https://github.com/dk949/serf_testrepo.git dir (nothrow)") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git dir (nothrow)") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }


    // does not throw with just 2 "arg"s because it matches the above case
    SECTION("serf clone arg arg (throws, too many args)") {
        auto argv = std::array {"serf", "clone", "arg", "arg", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}

TEST_CASE("delete", "[arghandler]") {
    // ### `serf delete [PATH]`
    SECTION("serf delete dir (nothrow") {
        auto argv = std::array {"serf", "delete", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf delete dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "delete", "dir", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}


TEST_CASE("checkout", "[arghandler]") {
    // ### `serf checkout [PATH] [BRANCH/TAG/COMMIT]`
    SECTION("serf checkout dir dev (nothrow") {
        auto argv = std::array {"serf", "checkout", "dir", "dev"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf checkout dir dev arg (throws, too many args)") {
        auto argv = std::array {"serf", "checkout", "dir", "dev", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}

TEST_CASE("update", "[arghandler]") {
    // ### `serf update`

    // ### `serf update [PATH]`

    SECTION("serf update (nothrow") {
        auto argv = std::array {"serf", "update"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf update dir (nothrow") {
        auto argv = std::array {"serf", "update", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf update dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "update", "dir", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}

TEST_CASE("latest", "[arghandler]") {
    // ### `serf latest [PATH]`
    SECTION("serf latest dir (nothrow") {
        auto argv = std::array {"serf", "latest", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf latest dir arg (throws, too many args") {
        auto argv = std::array {"serf", "latest", "dir", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}


TEST_CASE("pull", "[arghandler]") {
    // ### `serf pull`

    // ### `serf pull [PATH]`

    SECTION("serf pull (nothrow") {
        auto argv = std::array {"serf", "pull"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf pull dir (nothrow") {
        auto argv = std::array {"serf", "pull", "dir"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf pull dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "pull", "dir", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}

TEST_CASE("setup", "[arghandler]") {
    // ### `serf setup`
    SECTION("serf setup (nothrow") {
        auto argv = std::array {"serf", "setup"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf setup arg (throws, too many args") {
        auto argv = std::array {"serf", "setup", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}

TEST_CASE("no args", "[arghandler]") {
    // ### `serf`
    SECTION("serf (nothrow") {
        auto argv = std::array {"serf"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_NOTHROW(srf::getArgs(args));
    }

    SECTION("serf arg (throws, too many args") {
        auto argv = std::array {"serf", "arg"};
        auto args = ap::getArgsSpan(argv.size(), argv.data());

        CHECK_THROWS(srf::getArgs(args));
    }
}
