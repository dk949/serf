#include "argparse.hpp"

#include <cstring>

ap::ArgumentList::ArgumentList(std::initializer_list<Argument> args): m_args(args) {
    checkList();
}


void ap::ArgumentList::checkList() {
    if (m_args[0].optional || m_args[0].argName == ap::Argument::noName) {
        throw "Bad argument list. //TODO make this a real exception";
    }
}


std::optional<const char *> ap::ArgumentList::operator[](size_t index) const {
    if (m_args.size() < index) {
        return m_args[index].argName;
    }
    return std::nullopt;
}



ap::ArgParse &ap::ArgParse::add(std::initializer_list<Argument> argList) {
    m_argLists.emplace_back(argList);

    return *this;
}


ap::ArgParse &ap::ArgParse::noArgs() {
    return *this;
}


bool ap::ArgParse::present(const char *name) {
    for (const auto &i : m_argLists) {
        // checkList() ensures that this is fine to dereference
        if (std::strcmp(*i[0], name) == 0) {
            return true;
        }
    }
    return false;
}



#ifdef DEBUG
void ap::ArgParse::printDebug() {
    for (const auto &i : m_argLists) {
        for (const auto &j : i.getArgs()) {
            spdlog::info("Name: {}, optional: {}", j.argName ? j.argName : "None", j.optional);
        }
    }
}
#else
void ap::ArgParse::printDebug() {}
#endif
