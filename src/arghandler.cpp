#include "arghandler.hpp"

#include "argparse.hpp"  // for noName, ArgParse

#include <memory>  // for allocator



void srf::getArgs(std::span<const char *> args) {
    [[maybe_unused]] auto parsed = ap::ArgParse()
                                       .add({"init"}, "serf init")
                                       .add({"init", ap::noName}, "serf init [DIR_NAME]")
                                       .add({"clone", ap::noName}, "serf clone [REPO_URL]")
                                       .add({"clone", ap::noName, ap::noName}, "serf clone [REPO_URL] [PATH]")
                                       .add({"delete", ap::noName}, "serf delete [PATH]")
                                       .add({"checkout", ap::noName, ap::noName}, "serf checkout [PATH] [BRANCH/TAG/COMMIT]")
                                       .add({"update"}, "serf update")
                                       .add({"update", ap::noName}, "serf update [PATH]")
                                       .add({"latest", ap::noName}, "serf latest [PATH]")
                                       .add({"pull"}, "serf pull")
                                       .add({"pull", ap::noName}, "serf pull [PATH]")
                                       .add({"setup"}, "serf setup")
                                       .noArgs()
                                       .parse(args);
}
