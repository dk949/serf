#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP
#include <vector>
namespace ap {

/*! \class Argument argparse.hpp
 * \brief Basic building block of the argument parser.
 *
 * Holds information about one argument.
 * Single command can consist of one or more `Argument`s.
 *
 * \see `ArgParse::noArgs()` for case with 0 arguments.
 */
class Argument {
private:
    const char *m_argName;
    bool m_optional;

public:
    /*! \fn Argument::Argument(const char *argName, bool optional) argparse.hpp
     * \brief Constructor. Initialises the values `m_argName` and `m_optional`.
     *
     * \param argName name of the argument. Can be null.
     * \param optional whether this argument is optional on the command line.
     *
     * \note passing `ap::Argument::noName` for \p argName indicates that this argument can be anything
     *  and that its value needs to be saved.
     */
    Argument(const char *argName, bool optional);


    /*!
     * \brief Variable designating that an argument has no name.
     */
    static constexpr const char *noName = nullptr;


    bool isOptional();

    const char *getName();
};



class ArgumentList {
private:
    std::vector<Argument> m_args;

public:
    ArgumentList(std::initializer_list<Argument> args);

private:
    constexpr void checkList();
};



class ArgParse {
    std::vector<ArgumentList> m_argLists;

public:
    ArgParse() = default;

    ArgParse &add(std::initializer_list<Argument>);
    ArgParse &noArgs();
};

}  // namespace ap
#endif  // ARGPARSE_HPP
