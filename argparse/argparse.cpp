#include "argparse.hpp"

#include <cstring>
#include <numeric>
#include <span>
#include <stdexcept>

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

std::vector<const char *> ap::ArgumentList::getStrArgs() const {
    std::vector<const char *> out(m_args.size());
    std::generate(std::begin(out), std::end(out), [n = 0u, this]() mutable { return m_args[n++].argName; });
    return out;
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


std::optional<std::vector<const char *>> ap::ArgumentList::isSame(std::span<const char *> query) const {
    if (m_args.size() != query.size()) {
        return std::nullopt;
    }

    for (size_t i = 0; i < m_args.size(); i++) {
        if (m_args[i].argName != ap::Argument::noName && std::strcmp(m_args[i].argName, query[i]) != 0) {
            return std::nullopt;
        }
    }

    std::vector<const char *> out;
    std::copy_if(std::begin(query), std::end(query), std::back_inserter(out), [n = 0u, this](const char *) mutable {
        if (m_args[n++].argName == ap::Argument::noName) {
            return true;
        }
        return false;
    });
    return out;
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


const std::vector<ap::ArgumentList> &ap::ArgParse::getArgLists() const {
    return m_argLists;
}

ap::ParseResult ap::ArgParse::parse(std::span<const char *> args) {
    for (const auto &command : m_argLists) {
        if (auto res = command.isSame(args)) {
            return {command.getStrArgs(), res};
        }
    }
    throw std::logic_error("Could not parse");
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
