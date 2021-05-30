#include <iostream>
#include <spdlog/spdlog.h>
#include "gitpac.hpp"
int main(){
    spdlog::set_pattern("[%l]: %v");

    /* parse arguments here */

    auto value = "https://github.com/dk949/serf_testrepo0";
    auto difvalue = "https://github.com/dk949/serf_testrepo1";

    auto maybedif = "https://github.com/dk949/serf_testrepo0";

    spdlog::info("Hahing the value: {} gives hash: {}", value, std::hash<const char*>{}(value));
    spdlog::info("Hahing the value: {} again gives hash: {}", value, std::hash<const char*>{}(value));


    spdlog::info("Hahing another value: {} again gives hash: {}", difvalue, std::hash<const char*>{}(difvalue));

    spdlog::info("Hahing the same values twice gives {} result", std::hash<const char*>{}(value) == std::hash<const char*>{}(value)? "same": "different");
    spdlog::info("Hahing 2 similar values gives {} result", std::hash<const char*>{}(value) == std::hash<const char*>{}(difvalue)? "same": "different");

    return 0;
}
