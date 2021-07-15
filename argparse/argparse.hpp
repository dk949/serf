#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#ifdef DEBUG
#include <spdlog/spdlog.h>
#endif

#include <optional>
#include <vector>
namespace ap {

/*! \struct Argument argparse.hpp
 * \brief Basic building block of the argument parser.
 *
 * Holds information about one argument.
 * Single command can consist of one or more `Argument`s.
 *
 * \see `ArgParse::noArgs()` for case with 0 arguments.
 */
struct Argument {
    const char *argName;
    bool optional;

    /*!
     * \brief Variable designating that an argument has no name.
     */
    static constexpr const char *noName = nullptr;
};



class ArgumentList {
private:
    std::vector<Argument> m_args;

public:
    ArgumentList(std::initializer_list<Argument> args);

    const std::vector<Argument> &getArgs() const {
        return m_args;
    }

    std::optional<const char *> operator[](size_t index) const;

private:
    void checkList();
};



class ArgParse {
    std::vector<ArgumentList> m_argLists;

public:
    ArgParse() = default;

    ArgParse &add(std::initializer_list<Argument>);
    ArgParse &noArgs();

    bool present(const char *name);

    const ArgumentList &value(const char *name);



    void printDebug();
};

}  // namespace ap
#endif  // ARGPARSE_HPP
