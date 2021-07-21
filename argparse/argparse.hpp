#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <cstddef>           // for size_t
#include <initializer_list>  // for initializer_list
#include <iterator>          // for next
#include <optional>          // for optional
#include <span>              // for span
#include <string>            // for string
#include <vector>            // for vector

namespace ap {

static const std::string noName {};



class ArgumentList {
private:
    std::vector<std::string> m_args;


public:
    // cppcheck-suppress noExplicitConstructor; it is implicit on purpose
    ArgumentList(std::initializer_list<std::string> args);

    ArgumentList() = delete;

    const std::vector<std::string> &getArgs() const;

    size_t getDataScore() const;


    std::optional<std::string> operator[](size_t index) const;


    bool operator==(const ArgumentList &other) const;

    std::optional<std::vector<std::string>> isSame(const std::span<const char *> args) const;

    size_t size() const;



private:
    void checkList() const;
};


class ParseResult {
private:
    std::vector<std::string> m_args;
    std::optional<std::vector<std::string>> m_data;

public:
    ParseResult(std::vector<std::string> args, std::optional<std::vector<std::string>> data);

    bool is(const std::string &) const;

    bool has(const std::string &) const;

    const std::optional<std::vector<std::string>> &data() const;
};


class ArgParse {
    std::vector<ArgumentList> m_argLists;
    bool m_canBeNull = false;

public:
    ArgParse() = default;

    ArgParse &add(std::initializer_list<std::string> argList, const std::string &desc = {});
    ArgParse &noArgs();

    const std::vector<ArgumentList> &getArgLists() const;
    bool canBeNull() const;

    ParseResult parse(std::span<const char *> args);


    // cppcheck-suppress functionStatic; function can only be static in release mode
    void printDebug() const;
};

constexpr std::span<const char *> getArgsSpan(int argc, const char **argv) {
    if (argc > 1) {
        return std::span<const char *> {std::next(argv), static_cast<size_t>(argc) - 1u};
    }
    return std::span<const char *> {};
}
}  // namespace ap



#endif  // ARGPARSE_HPP
