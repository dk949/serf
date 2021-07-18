#include "argparse.hpp"

#include <cstring>
#include <numeric>
#include <span>
#include <stdexcept>

// TODO: use str_t instead of const char *
// TODO: add possibility to add some valiation lambda for noName args

ap::Argument::Argument(const char *argName): m_argName(argName) {};
ap::Argument::operator const char *() const {
    return m_argName;
}

ap::Argument::operator bool() const {
    return m_argName;
}

namespace ap {
bool operator==(const Argument &This, const char *other) {
    if (This.m_argName != nullptr && other != nullptr) {
        return std::strcmp(This.m_argName, other) == 0;
    }
    return This.m_argName == other;
}

bool operator==(const Argument &This, const Argument &other) {
    return This == other.m_argName;
}
}  // namespace ap

ap::ArgumentList::ArgumentList(std::initializer_list<Argument> args): m_args(args) {
    checkList();
}


void ap::ArgumentList::checkList() {
    if (m_args.size() < 1) {
        throw std::logic_error("Empty argument list");
    }
    if (m_args[0] == ap::Argument::noName) {
        throw std::logic_error("1st argument cannot be noName");
    }
}


const std::vector<ap::Argument> &ap::ArgumentList::getArgs() const {
    return m_args;
}

std::optional<const char *> ap::ArgumentList::operator[](size_t index) const {
    if (m_args.size() > index) {
        return m_args[index];
    }
    return std::nullopt;
}

bool ap::ArgumentList::operator==(const ArgumentList &other) const {
    if (m_args.size() != other.m_args.size()) {
        return false;
    }

    for (size_t i = 0; i < m_args.size(); i++) {
        if (m_args[i] != other.m_args[i]) {
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
        if (m_args[i] != ap::Argument::noName && m_args[i] != query[i]) {
            return std::nullopt;
        }
    }

    std::vector<const char *> out;
    std::copy_if(std::begin(query), std::end(query), std::back_inserter(out), [n = 0u, this](const char *) mutable {
        if (m_args[n++] == ap::Argument::noName) {
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
    m_canBeNull = true;
    return *this;
}


const std::vector<ap::ArgumentList> &ap::ArgParse::getArgLists() const {
    return m_argLists;
}

ap::ParseResult ap::ArgParse::parse(std::span<const char *> args) {
    if (args.size() == 0 && m_canBeNull) {
        return {{}, std::nullopt};
    }

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
            spdlog::info("Name: {}", j ? j : "noName");
        }
    }
}
#else
void ap::ArgParse::printDebug() {}
#endif
