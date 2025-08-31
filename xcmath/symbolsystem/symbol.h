#pragma once
#ifndef XCMATH_SYMBOLSYSTEM_SYMBOL_H
#define XCMATH_SYMBOLSYSTEM_SYMBOL_H
#include <string>
#include "./monomial.h"
#include "./xcmathConfig.h"
namespace xcmath {
class XCMATH_API Symbol {
   private:
    std::string __name;

   public:
    Symbol(const std::string &name);
    const std::string &name() const;

    operator Monomial();
};
}  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_SYMBOL_H
