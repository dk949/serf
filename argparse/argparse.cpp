#include "argparse.hpp"

#ifdef DEBUG
#include <fmt/format.h>     // for format_to
#include <spdlog/spdlog.h>  // for info
#endif

#include <algorithm>  // for copy_if, find_if, sort
#include <numeric>    // for accumulate
#include <span>       // for span
#include <stdexcept>  // for logic_error
#include <utility>    // for move

// TODO: add possibility to add some valiation lambda for noName args

ap::ArgumentList::ArgumentList(std::initializer_list<std::string> args): m_args(args) {
    checkList();
}


void ap::ArgumentList::checkList() const {
    if (m_args.empty()) {
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
    return std::accumulate(std::begin(m_args), std::end(m_args), 0u, [n = 1u](unsigned int a, const std::string &b) mutable {
        return a + static_cast<unsigned int>(b == ap::noName) * n++;
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
    // NOLINTNEXTLINE [hicpp-named-parameter,readability-named-parameter]// this parameter is not needed
    std::copy_if(std::begin(query), std::end(query), std::back_inserter(out), [n = 0u, this](const std::string &) mutable {
        return m_args[n++] == ap::noName;
    });
    return out;
}



ap::ParseResult::ParseResult(std::vector<std::string> args, std::optional<std::vector<std::string>> data):
        m_args(std::move(args)), m_data(std::move(data)) {}

bool ap::ParseResult::is(const std::string &argName) const {
    if (m_args.empty()) {
        return argName.empty();
    }
    return m_args[0] == argName;
}

bool ap::ParseResult::is() const {
    return m_args.empty();
}

bool ap::ParseResult::has(const std::string &argName) const {
    return std::find_if(std::begin(m_args) + 1, std::end(m_args), [&argName](const auto &arg) { return arg == argName; }) !=
           std::end(m_args);
}

const std::optional<std::vector<std::string>> &ap::ParseResult::data() const {
    return m_data;
}



ap::ArgParse &ap::ArgParse::add(std::initializer_list<std::string> argList, [[maybe_unused]] const std::string &desc) {
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

std::optional<ap::ParseResult> ap::ArgParse::parse(std::span<const char *> args) {
    /*
    Problem:
        if 2 `ArgumentList` exist where 1st has a named `Argument` where second one has data,
        named argument can get interpreted as data

    Solution:
        make `ArgumentList` sortable in such a way that lists with no data get moved to the beginning
        then sort m_argLists
       */


    std::sort(std::begin(m_argLists), std::end(m_argLists), [](const ArgumentList &a, const ArgumentList &b) {
        return a.getDataScore() < b.getDataScore();
    });


    if (args.empty() && m_canBeNull) {
        return ap::ParseResult{{}, std::nullopt};
    }

    for (const auto &command : m_argLists) {
        // cppcheck-suppress useStlAlgorithm; false positive for find_if
        if (auto res = command.isSame(args)) {
            return ap::ParseResult{command.getArgs(), res->empty() ? std::nullopt : res};
        }
    }
    return std::nullopt;
}


#ifdef DEBUG
void ap::ArgParse::printDebug() const {
    for (const auto &i : m_argLists) {
        for (const auto &j : i.getArgs()) {
            spdlog::info("Name: {}", !j.empty() ? j : "noName");
        }
    }
}
#else
void ap::ArgParse::printDebug() const {}
#endif
