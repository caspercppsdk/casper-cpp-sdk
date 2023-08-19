#pragma once

#include <cstring>
#include <string>
#include <locale>

#include <boost/algorithm/hex.hpp>
#include <boost/property_tree/ptree.hpp>

namespace Casper::algorithm
{
namespace details
{
template <typename>
struct string_size_impl;

template <size_t N>
struct string_size_impl<const char[N]>
{
    static constexpr size_t size(const char (&)[N]) { return N - 1; }
};

template <size_t N>
struct string_size_impl<char[N]>
{
    static constexpr size_t size(char (&s)[N]) { return N ? strlen(s) : 0; }
};

template <>
struct string_size_impl<const char*>
{
    static constexpr size_t size(const char* s) { return s ? strlen(s) : 0; }
};

template <>
struct string_size_impl<char*>
{
    static size_t size(char* s) { return s ? strlen(s) : 0; }
};

template <>
struct string_size_impl<std::string>
{
    static size_t size(const std::string& s) { return s.size(); }
};

template <>
struct string_size_impl<std::string_view>
{
    static size_t size(std::string_view s) { return s.size(); }
};

template <typename String>
size_t string_size(String&& s)
{
    using noref_t = typename std::remove_reference_t<String>;
    using string_t = typename std::conditional_t<std::is_array_v<noref_t>, noref_t, typename std::remove_cv_t<noref_t>>;
    return string_size_impl<string_t>::size(s);
}

template <typename...>
struct concatenate_impl;

template <typename String>
struct concatenate_impl<String>
{
    static size_t size(String&& s) { return string_size(s); }
    static void concatenate(std::string& result, String&& s) { result += s; }
};

template <typename String, typename... Rest>
struct concatenate_impl<String, Rest...>
{
    static size_t size(String&& s, Rest&&... rest)
    {
        return string_size(s) + concatenate_impl<Rest...>::size(std::forward<Rest>(rest)...);
    }
    static void concatenate(std::string& result, String&& s, Rest&&... rest)
    {
        result += s;
        concatenate_impl<Rest...>::concatenate(result, std::forward<Rest>(rest)...);
    }
};

} // namespace details

template <typename... Strings>
std::string join(Strings&&... strings)
{
    std::string result;
    result.reserve(details::concatenate_impl<Strings...>::size(std::forward<Strings>(strings)...));
    details::concatenate_impl<Strings...>::concatenate(result, std::forward<Strings>(strings)...);
    return result;
}

} // namespace Casper::algorithm
