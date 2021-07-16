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

/*! \struct Argument argparse.hpp
 * \brief Basic building block of the argument parser.
 *
 * Holds information about one argument.
 * Single command can consist of one or more `Argument`s.
 *
 * \see `ArgParse::noArgs()` for case with 0 arguments.
 */
struct Argument {
    bool operator==(const Argument &) const = default;
    /*! \var argName argparse.hpp
     * \brief Name of the argument
     *
     * This is the name by which it will be identified in the future
     * \note if this value is `ap::Argument::noName` it is interprreted as "user can pass in any value and this value will be saved".
     */
    const char *argName;


    /*! \var optional argparse.hpp
     * \brief Argument is not required if this value is true
     */
    bool optional;

    /*! \var noName argparse.hpp
     * \brief Variable designating that an argument has no name.
     */
    static constexpr const char *noName = nullptr;
};



/*! \class ap::ArgumentList argparse.hpp
 * \brief List of arguments comprising a single command.
 *
 * Holds a `std::vector` of `Argument`s representing a single command.
 */
class ArgumentList {
private:
    std::vector<Argument> m_args;

public:
    /*! \fn ap::ArgumentList::ArgumentList(std::initializer_list<Argument> args) argparse.hpp
     * \brief Constructs the vector of `Argument`s from the `std::initializer_list`.
     *
     * Also makes sure the first `Argument` is not optional and is not `ap::Argument::noName`
     *
     * \param args list of `ap::Argument`s that make up this argument list.
     * \throws std::logic_error if `ap::Argument::optional` is `true` for the first argument or if its
     * `ap::Argument::argName` is `ap::Argument::noName`
     * \throws std::logic_error if \p args is empty
     */
    ArgumentList(std::initializer_list<Argument> args);

    ArgumentList() = delete;

    const std::vector<Argument> &getArgs() const;


    /*! \fn std::optional<const char *> ap::ArgumentList::operator[](size_t index) const argparse.hpp
     * \brief  Get the `argName` of the `index`<sup>th</sup> `ap::Argument`;
     *
     * If the argument exists, its `ap::Argument::argName` is returned, otherwise `std::nullopt` is returned
     * \param index index of the `ap::Argument` to get
     * \return `ap::Argument::argName` if argument exists, otherwise `std::nullopt`
     */
    std::optional<const char *> operator[](size_t index) const;


    /*!
     * \brief Compares two `ap::ArgumentList`s ignoreing `ap::Argument::optional` component.
     */
    bool operator==(const ArgumentList &other) const;

    std::optional<std::vector<const char *>> isSame(const std::span<const char *> args) const;


    /*! \fn size_t ap::ArgumentList::size() const argparse.hpp
     * \brief get the number of arguments in the list
     *
     * \return number of arguemnts
     */
    size_t size() const;



private:
    void checkList();
};


class ParseResult {
private:
    std::vector<const char *> m_args;
    std::optional<std::vector<const char *>> m_data;

public:
    ParseResult(std::vector<const char *> args, std::optional<std::vector<const char *>> data);

    bool is(const char *argName) const;

    bool has(const char *argName) const;

    const std::optional<std::vector<const char *>> &data() const;
};


class ArgParse {
    std::vector<ArgumentList> m_argLists;

public:
    ArgParse() = default;

    ArgParse &add(std::initializer_list<Argument> argList);
    ArgParse &noArgs();

    bool validate(std::initializer_list<Argument> argList);

    ParseResult parse(const size_t argc, const char **argv);
    void printDebug();
};

}  // namespace ap
#endif  // ARGPARSE_HPP
