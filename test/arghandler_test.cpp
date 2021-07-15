#include "../src/arghandler.hpp"

#include <catch2/catch.hpp>

TEST_CASE("init", "[arghandler]") {
    //### `serf init`
    //### `serf init [DIR_NAME]`

    SECTION("serf init (nothrow)") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init"};
        const int argc = argv.size();

        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf init dir (nothrow)") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init", "dir"};
        const int argc = argv.size();

        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf init dir arg (throws, too many args") {
        auto argv = std::array {"serf", "init", "dir", "arg"};
        const int argc = argv.size();

        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("clone", "[arghandler]") {
    //    ### `serf clone [REPO_URL] [PATH]`
    //    ### `serf clone [REPO_URL]`
    SECTION("serf clone https://github.com/dk949/serf_testrepo.git (nothrow)") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git (nothrow)") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone https://github.com/dk949/serf_testrepo.git dir (nothrow)") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git dir (nothrow)") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }


    SECTION("serf clone arg arg (throws, too many args)") {
        auto argv = std::array {"serf", "clone", "arg", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("delete", "[arghandler]") {
    // ### `serf delete [PATH]`
    SECTION("serf delete dir (nothrow") {
        auto argv = std::array {"serf", "delete", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf delete dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "delete", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("checkout", "[arghandler]") {
    // ### `serf checkout [PATH] [BRANCH/TAG/COMMIT]`
    SECTION("serf checkout dir dev (nothrow") {
        auto argv = std::array {"serf", "checkout", "dir", "dev"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf checkout dir dev arg (throws, too many args)") {
        auto argv = std::array {"serf", "checkout", "dir", "dev", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("update", "[arghandler]") {
    // ### `serf update`

    // ### `serf update [PATH]`

    SECTION("serf update (nothrow") {
        auto argv = std::array {"serf", "update"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf update dir (nothrow") {
        auto argv = std::array {"serf", "update", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf update dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "update", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("latest", "[arghandler]") {
    // ### `serf latest [PATH]`
    SECTION("serf latest dir (nothrow") {
        auto argv = std::array {"serf", "latest", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf latest dir arg (throws, too many args") {
        auto argv = std::array {"serf", "latest", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("pull", "[arghandler]") {
    // ### `serf pull`

    // ### `serf pull [PATH]`

    SECTION("serf pull (nothrow") {
        auto argv = std::array {"serf", "pull"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf pull dir (nothrow") {
        auto argv = std::array {"serf", "pull", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf pull dir arg (throws, too many args)") {
        auto argv = std::array {"serf", "pull", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("setup", "[arghandler]") {
    // ### `serf setup`
    SECTION("serf setup (nothrow") {
        auto argv = std::array {"serf", "setup"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf setup arg (throws, too many args") {
        auto argv = std::array {"serf", "setup", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("no args", "[arghandler]") {
    // ### `serf`
    SECTION("serf (nothrow") {
        auto argv = std::array {"serf"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf arg (throws, too many args") {
        auto argv = std::array {"serf", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}
