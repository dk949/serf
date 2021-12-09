#ifndef URL_HPP
#define URL_HPP

#include <ctre.hpp>
#include <optional>
#include <regex>
#include <string>


namespace gp {

class URL {
private:
    std::string m_url;

private:
    explicit URL(const std::string &url): m_url(url) {}

public:
    static std::optional<URL> makeUrl(const std::string &url) {
        if (urlOk(url)) {
            return URL {url};
        }
        return std::nullopt;
    }

    std::string &str() {
        return m_url;
    }
    const std::string &str() const {
        return m_url;
    }


private:
    // Will probably match a lot of URLs before it breaks
    static constexpr ctll::fixed_string urlPattern {
        R"(^(https?://)?(www)?[\+_\-a-zA-Z0-9]{1,256}\.[a-zA-Z]{1,4}[~:\+@#/\._\-a-zA-Z0-9]*$)"};

    static constexpr auto urlMatch = ctre::match<urlPattern>;

    static_assert(ctre::match<urlPattern>("https://www.google.com/test"));
    static_assert(ctre::match<urlPattern>("https://google.com/test"));
    static_assert(ctre::match<urlPattern>("http://google.com/test"));
    static_assert(ctre::match<urlPattern>("google.com/test"));
    static_assert(ctre::match<urlPattern>("go-ogle.com/test"));
    static_assert(ctre::match<urlPattern>("go_ogle.com/test"));
    static_assert(ctre::match<urlPattern>("go+ogle.com/test"));
    static_assert(ctre::match<urlPattern>("google.com/test@"));
    static_assert(ctre::match<urlPattern>("google.com/test#"));
    static_assert(ctre::match<urlPattern>("google.com/test+"));
    static_assert(ctre::match<urlPattern>("google.com/test_"));
    static_assert(ctre::match<urlPattern>("google.com/test-"));
    static_assert(ctre::match<urlPattern>("google.com/test:"));
    static_assert(ctre::match<urlPattern>("google.com/test~"));

    static constexpr bool urlOk(std::string_view url) {
        return bool(urlMatch(url));
    }
};


}  // namespace gp

#endif  // URL_HPP
