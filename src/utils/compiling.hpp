// compiling.hpp
#ifndef COMPILING_H
#define COMPILING_H
#include <cstddef>
#include <string_view>

namespace xcmath {
template <char... args>
struct static_string {
    static constexpr const char str[] = {args...};
    operator const char*() const { return static_string::str; }
};
template <typename Object>
constexpr auto get_type_name() {
#ifdef _MSC_VER
    constexpr std::string_view fully_name = __FUNCSIG__;
#else
    constexpr std::string_view fully_name = __PRETTY_FUNCTION__;
#endif
#ifdef __clang__
    constexpr size_t begin =
        sizeof("auto __cdecl xcmath::get_type_name(void) [Object = ") - 1;
    constexpr size_t end = fully_name.rfind("]");
#else
    constexpr size_t begin = fully_name.find("<") + 1;
    constexpr size_t end = fully_name.rfind(">");
#endif
    constexpr auto type_name_view = fully_name.substr(begin, end - begin);
    constexpr auto indices = std::make_index_sequence<type_name_view.size()>();
    constexpr auto type_name =
        [&]<std::size_t... indices>(
            std::integer_sequence<std::size_t, indices...>) {
            constexpr auto str =
                static_string<type_name_view[indices]..., '\0'>();
            return str;
        }(indices);
    return type_name;
}
}  // namespace xcmath

#endif  // COMPILING_H