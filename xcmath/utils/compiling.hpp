// compiling.hpp
#pragma once
#ifndef COMPILING_H
#define COMPILING_H
#include <cstddef>
#include <string_view>

namespace xcmath {
template <char... args>
struct static_string {
    static constexpr const char str[] = {args...};
    constexpr operator const char*() const { return static_string::str; }
};
template <size_t N, const char (&str)[N]>
struct MyStr {};
#ifdef __unix
template <class _Tp>
constexpr auto TypeName = []<class _FTp = _Tp>() -> const char* {
    constexpr std::string_view full_name(__PRETTY_FUNCTION__);
    constexpr auto start = full_name.find("=") + 2;
    constexpr auto end = full_name.find("]");
    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        return static_string<full_name[idx + start]..., '\0'>{};
    }(std::make_index_sequence<end - start>{});
}();
#else
template <typename Object>
constexpr auto TypeName = []<class _Obj = Object>() {

#ifdef _MSC_VER
    constexpr std::string_view fully_name = __FUNCSIG__;
#else
    constexpr std::string_view fully_name = __PRETTY_FUNCTION__;
#endif
#ifdef __clang__
    constexpr size_t begin = sizeof(
                                 "auto __cdecl xcmath::(anonymous "
                                 "class)::operator()(void) const [_Obj = ") -
                             1;
    constexpr size_t end = fully_name.rfind("]");
#elif defined(__GNUC__)
    constexpr size_t begin = sizeof("<lambda()> [with _Obj =");
    constexpr size_t end = fully_name.rfind("]");
#else
    constexpr size_t begin = fully_name.find("<") + 1;
    constexpr size_t end = fully_name.rfind(">");
#endif

      constexpr auto type_name_view = fully_name.substr(begin, end - begin);
      return [&]<size_t... index>(std::index_sequence<index...>) {
          return static_string<type_name_view[index]..., '\0'>{};
      }((std::make_index_sequence<end - begin>{}));
}();
#endif
}  // namespace xcmath

#endif  // COMPILING_H
