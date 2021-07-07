#include "../src/arghandler.hpp"

#include <catch2/catch.hpp>

/// These should not throw
TEST_CASE("init success", "[arghandler][success]") {
    //### `serf init`
    //### `serf init [DIR_NAME]`

    SECTION("serf init") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init"};
        const int argc = argv.size();

        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf init dir") {  // ccls is really struggling here
        auto argv = std::array {"serf", "init", "dir"};
        const int argc = argv.size();

        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("clone success", "[arghandler][success]") {
    //    ### `serf clone [REPO_URL] [PATH]`
    //    ### `serf clone [REPO_URL]`
    SECTION("serf clone https://github.com/dk949/serf_testrepo.git") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone https://github.com/dk949/serf_testrepo.git dir") {
        auto argv = std::array {"serf", "clone", "https://github.com/dk949/serf_testrepo.git", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf clone git@github.com:dk949/serf_testrepo.git dir") {
        auto argv = std::array {"serf", "clone", "git@github.com:dk949/serf_testrepo.git", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("delete success", "[arghandler][success]") {
    // ### `serf delete [PATH]`
    SECTION("serf delete dir") {
        auto argv = std::array {"serf", "delete", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("checkout success", "[arghandler][success]") {
    // ### `serf checkout [PATH] [BRANCH/TAG/COMMIT]`
    SECTION("serf checkout dir dev") {
        auto argv = std::array {"serf", "checkout", "dir", "dev"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("update success", "[arghandler][success]") {
    // ### `serf update`

    // ### `serf update [PATH]`

    SECTION("serf update") {
        auto argv = std::array {"serf", "update"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf update dir") {
        auto argv = std::array {"serf", "update", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("latest success", "[arghandler][success]") {
    // ### `serf latest [PATH]`
    SECTION("serf latest dir") {
        auto argv = std::array {"serf", "latest", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("pull success", "[arghandler][success]") {
    // ### `serf pull`

    // ### `serf pull [PATH]`

    SECTION("serf pull") {
        auto argv = std::array {"serf", "pull"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }

    SECTION("serf pull dir") {
        auto argv = std::array {"serf", "pull", "dir"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("setup success", "[arghandler][success]") {
    // ### `serf setup`
    SECTION("serf setup") {
        auto argv = std::array {"serf", "setup"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("no args success", "[arghandler][success]") {
    // ### `serf`
    SECTION("serf") {
        auto argv = std::array {"serf"};
        const int argc = argv.size();
        CHECK_NOTHROW(srf::getArgs(argc, argv.data()));
    }
}

/// These should throw
TEST_CASE("init fail", "[arghandler][fail]") {
    SECTION("serf init dir arg") {
        auto argv = std::array {"serf", "init", "dir", "arg"};
        const int argc = argv.size();

        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}


TEST_CASE("clone fail", "[arghandler][fail]") {
    SECTION("serf clone arg arg") {
        auto argv = std::array {"serf", "clone", "arg", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("delete fail", "[arghandler][fail]") {
    SECTION("serf delete dir arg") {
        auto argv = std::array {"serf", "delete", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("checkout fail", "[arghandler][fail]") {
    SECTION("serf checkout dir dev arg") {
        auto argv = std::array {"serf", "checkout", "dir", "dev", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("update fail", "[arghandler][fail]") {
    SECTION("serf update dir arg") {
        auto argv = std::array {"serf", "update", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("latest fail", "[arghandler][fail]") {
    SECTION("serf latest dir arg") {
        auto argv = std::array {"serf", "latest", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("pull fail", "[arghandler][fail]") {
    SECTION("serf pull dir arg") {
        auto argv = std::array {"serf", "pull", "dir", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("setup fail", "[arghandler][fail]") {
    SECTION("serf setup arg") {
        auto argv = std::array {"serf", "setup", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}

TEST_CASE("noargs fail", "[arghandler][fail]") {
    SECTION("serf") {
        auto argv = std::array {"serf", "arg"};
        const int argc = argv.size();
        CHECK_THROWS(srf::getArgs(argc, argv.data()));
    }
}