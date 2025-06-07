#ifndef XCMATH_CONFIG_H
#define XCMATH_CONFIG_H

#ifdef XCMATH_EXPORTS
#   if defined(_WIN32) || defined(_WIN64)
#      define XCMATH_API __declspec(dllexport)
#   elif defined(__GNUC__) || defined(__clang__)
#       define XCMATH_API __attribute__((visibility("default")))
#   else
#       define XCMATH_API
#   endif
#else
#   define XCMATH_API
#endif

#endif  // XCMATH_CONFIG_H