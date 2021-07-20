#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#ifdef DEBUG
#include <csignal>
#include <spdlog/spdlog.h>
#endif

#include <compare>
#include <optional>
#include <span>
#include <vector>

namespace ap {

static const std::string noName {};



class ArgumentList {
private:
    std::vector<std::string> m_args;


public:
    ArgumentList(std::initializer_list<std::string> args);

    ArgumentList() = delete;

    const std::vector<std::string> &getArgs() const;

    size_t getDataScore() const;


    std::optional<std::string> operator[](size_t index) const;


    bool operator==(const ArgumentList &other) const;

    std::optional<std::vector<std::string>> isSame(const std::span<const char *> args) const;


    /*! \fn size_t ap::ArgumentList::size() const argparse.hpp
     * \brief get the number of arguments in the list
     * \return number of arguemnts
     */
    size_t size() const;



private:
    void checkList();
};


class ParseResult {
private:
    std::vector<std::string> m_args;
    std::optional<std::vector<std::string>> m_data;

public:
    ParseResult(std::vector<std::string> args, std::optional<std::vector<std::string>> data);

    bool is(std::string) const;

    bool has(std::string) const;

    const std::optional<std::vector<std::string>> &data() const;
};


class ArgParse {
    std::vector<ArgumentList> m_argLists;
    bool m_canBeNull = false;

public:
    ArgParse() = default;

    ArgParse &add(std::initializer_list<std::string> argList);
    ArgParse &noArgs();

    const std::vector<ArgumentList> &getArgLists() const;
    bool canBeNull() const;

    ParseResult parse(std::span<const char *> args);
    void printDebug();
};

}  // namespace ap
#endif  // ARGPARSE_HPP
