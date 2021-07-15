#include "argparse.hpp"

#include <spdlog/spdlog.h>

ap::Argument::Argument(const char *argName, bool optional): m_argName(argName), m_optional(optional) {}



bool ap::Argument::isOptional() {
    return m_optional;
}

const char *ap::Argument::getName() {
    return m_argName;
}



ap::ArgumentList::ArgumentList(std::initializer_list<Argument> args): m_args(args) {
    checkList();
}


constexpr void ap::ArgumentList::checkList() {
    if (m_args[0].isOptional() || m_args[0].getName() == ap::Argument::noName) {
        throw "Bad argument list. //TODO make this a real exception";
    }
}



ap::ArgParse &ap::ArgParse::add(std::initializer_list<Argument> argList) {
    m_argLists.emplace_back(argList);

    return *this;
}


ap::ArgParse &ap::ArgParse::noArgs() {
    return *this;
}
