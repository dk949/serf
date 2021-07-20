#include "argparse.hpp"

#include <cstring>
#include <numeric>
#include <span>
#include <stdexcept>

// TODO: use str_t instead of const char *
// TODO: add possibility to add some valiation lambda for noName args

ap::ArgumentList::ArgumentList(std::initializer_list<std::string> args): m_args(args) {
    checkList();
}


void ap::ArgumentList::checkList() {
    if (m_args.size() < 1) {
        throw std::logic_error("Empty argument list");
    }
    if (m_args[0] == ap::noName) {
        throw std::logic_error("1st argument cannot be noName");
    }
}


const std::vector<std::string> &ap::ArgumentList::getArgs() const {
    return m_args;
}


size_t ap::ArgumentList::getDataScore() const {
    return std::accumulate(std::begin(m_args), std::end(m_args), 0u, [n = 1u](size_t a, const std::string &b) mutable {
        return a + (b.data() == ap::noName) * n++;
    });
}

std::optional<std::string> ap::ArgumentList::operator[](size_t index) const {
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


std::optional<std::vector<std::string>> ap::ArgumentList::isSame(std::span<const char *> query) const {
    if (m_args.size() != query.size()) {
        return std::nullopt;
    }

    for (size_t i = 0; i < m_args.size(); i++) {
        if (m_args[i] != ap::noName && m_args[i] != query[i]) {
            return std::nullopt;
        }
    }

    std::vector<std::string> out;
    std::copy_if(std::begin(query), std::end(query), std::back_inserter(out), [n = 0u, this](const char *) mutable {
        if (m_args[n++] == ap::noName) {
            return true;
        }
        return false;
    });
    return out;
}



ap::ParseResult::ParseResult(std::vector<std::string> args, std::optional<std::vector<std::string>> data):
        m_args(std::move(args)), m_data(std::move(data)) {}

bool ap::ParseResult::is(std::string argName) const {
    return m_args[0] == argName;
}

bool ap::ParseResult::has(std::string argName) const {
    return std::find_if(std::begin(m_args) + 1, std::end(m_args), [&argName](const auto &arg) {
        return arg == argName;
    }) != std::end(m_args);
}

const std::optional<std::vector<std::string>> &ap::ParseResult::data() const {
    return m_data;
}



ap::ArgParse &ap::ArgParse::add(std::initializer_list<std::string> argList) {
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

bool ap::ArgParse::canBeNull() const {
    return m_canBeNull;
}

ap::ParseResult ap::ArgParse::parse(std::span<const char *> args) {
    /*
    Problem:
        if 2 `ArgumentList` exist where 1st has a named `Argument` where second one has data,
        named argument can get interpreted as data

    Solution:
        make `ArgumentList` sortable in such a way that lists with no data get moved to the beginning
        then sort m_argLists
       */


    std::sort(std::begin(m_argLists), std::end(m_argLists), [](const ArgumentList &a, const ArgumentList &b) {
        return a.getDataScore() > b.getDataScore();
    });


    if (args.size() == 0 && m_canBeNull) {
        return {{}, std::nullopt};
    }

    for (const auto &command : m_argLists) {
        if (auto res = command.isSame(args)) {
            return {command.getArgs(), res};
        }
    }
    throw std::logic_error("Could not parse");
}


#ifdef DEBUG
void ap::ArgParse::printDebug() {
    for (const auto &i : m_argLists) {
        for (const auto &j : i.getArgs()) {
            spdlog::info("Name: {}", !j.empty() ? j : "noName");
        }
    }
}
#else
void ap::ArgParse::printDebug() {}
#endif
