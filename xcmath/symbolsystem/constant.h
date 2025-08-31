#pragma once
#ifndef XCMATH_SYMBOLSYSTEM_CONSTANT_H
#define XCMATH_SYMBOLSYSTEM_CONSTANT_H

#include "./xcmathConfig.h"
namespace xcmath {
class Symbol;
class XCMATH_API Constant {
   public:
    Constant() = default;
    ~Constant() = default;

    virtual Constant& operator+();
};
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_CONSTANT_H