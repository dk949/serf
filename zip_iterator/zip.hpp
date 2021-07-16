#ifndef ZIP_HPP
#define ZIP_HPP
#include <array>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <optional>
#include <span>
#include <vector>

namespace util {
template<typename ValFirst, typename ValSecond>
struct zip_iterator {
private:
    using value_typeFirst = ValFirst;
    using value_typeSecond = ValSecond;

    using pointerFirst = ValFirst *;
    using pointerSecond = ValSecond *;

    using referenceFirst = ValFirst &;
    using referenceSecond = ValSecond &;

public:
    using value_type = std::pair<value_typeFirst, value_typeSecond>;
    using pointer = std::pair<pointerFirst, pointerSecond>;
    using reference = std::pair<referenceFirst, referenceSecond>;

private:
    pointer m_pointers;

public:
    zip_iterator(pointer pointers): m_pointers(pointers) {}

    // prefix increment
    zip_iterator &operator++() noexcept {
        m_pointers.first++;
        m_pointers.second++;
        return *this;
    }

    // postfix increment
    zip_iterator operator++(int) noexcept {
        zip_iterator it = *this;
        ++(*this);
        return it;
    }

    // prefix decrement
    zip_iterator &operator--() noexcept {
        m_pointers.first++;
        m_pointers.second++;
        return *this;
    }

    // postfix decrement
    zip_iterator operator--(int) noexcept {
        zip_iterator it = *this;
        --(*this);
        return it;
    }

    // index access
    reference operator[](size_t index) noexcept {
        return std::make_pair<referenceFirst, referenceSecond>(*(m_pointers.first + index), *(m_pointers.second + index));
    }


    // dereference
    reference operator*() noexcept {
        return std::pair<referenceFirst, referenceSecond> {*m_pointers.first, *m_pointers.second};
    }

    // equality
    bool operator==(const zip_iterator &other) const noexcept {
        return m_pointers.first == other.m_pointers.first && m_pointers.second == other.m_pointers.second;
    }

    // inequality
    bool operator!=(const zip_iterator &other) const noexcept {
        return !(*this == other);
    }
};

template<typename First, typename Second>
struct Zip {
public:
    using iterator =
        zip_iterator<typename std::iterator_traits<typename First::iterator>::value_type, typename std::iterator_traits<typename Second::iterator>::value_type>;

private:
    First m_first;
    Second m_second;
    size_t m_size;

public:
    Zip(First first, Second second): m_first(first), m_second(second), m_size(first.size()) {};
    Zip(First first, Second second, size_t size): m_first(first), m_second(second), m_size(size) {};

    iterator begin() {
        return iterator(std::make_pair(std::begin(m_first), std::begin(m_second)));
    }

    iterator end() {
        return iterator(std::make_pair(std::begin(m_first) + m_size, std::begin(m_second) + m_size));
    }
};

}  // namespace util
#endif  // ZIP_HPP
