#include "argparse.hpp"

#include <cstring>
#include <numeric>
#include <span>

ap::ArgumentList::ArgumentList(std::initializer_list<Argument> args): m_args(args) {
    if (args.size() < 1) {
        throw std::logic_error("Empty argument list");
    }
    checkList();
}


void ap::ArgumentList::checkList() {
    if (m_args[0].optional || m_args[0].argName == ap::Argument::noName) {
        throw std::logic_error("Bad argument list.");
    }
}


const std::vector<ap::Argument> &ap::ArgumentList::getArgs() const {
    return m_args;
}

std::optional<const char *> ap::ArgumentList::operator[](size_t index) const {
    if (m_args.size() > index) {
        return m_args[index].argName;
    }
    return std::nullopt;
}

bool ap::ArgumentList::operator==(const ArgumentList &other) const {
    if (m_args.size() != other.m_args.size()) {
        return false;
    }

    for (size_t i = 0; i < m_args.size(); i++) {
        if (std::strcmp(m_args[i].argName, other.m_args[i].argName) != 0) {
            return false;
        }
    }

    return true;
}

size_t ap::ArgumentList::size() const {
    return m_args.size();
}



ap::ParseResult::ParseResult(std::vector<const char *> args, std::optional<std::vector<const char *>> data):
        m_args(std::move(args)), m_data(std::move(data)) {}

bool ap::ParseResult::is(const char *argName) const {
    return std::strcmp(m_args[0], argName) == 0;
}

bool ap::ParseResult::has(const char *argName) const {
    return std::find_if(std::begin(m_args) + 1, std::end(m_args), [&argName](const auto &arg) {
        return std::strcmp(arg, argName) == 0;
    }) != std::end(m_args);
}

const std::optional<std::vector<const char *>> &ap::ParseResult::data() const {
    return m_data;
}



ap::ArgParse &ap::ArgParse::add(std::initializer_list<Argument> argList) {
    m_argLists.emplace_back(argList);

    return *this;
}


ap::ArgParse &ap::ArgParse::noArgs() {
    return *this;
}


bool ap::ArgParse::validate(std::initializer_list<Argument> argList) {
    return std::find(std::begin(m_argLists), std::end(m_argLists), argList) != std::end(m_argLists);
}



ap::ParseResult ap::ArgParse::parse(const size_t argc, const char **argv) {
    std::span args {argv[1], argc - 1};


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
