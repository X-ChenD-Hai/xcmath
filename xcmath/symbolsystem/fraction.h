#pragma once
#ifndef XCMATH_SYMBOLSYSTEM_FRACTION_H
#define XCMATH_SYMBOLSYSTEM_FRACTION_H
#include <vector>

#include "./ops/ops.h"
#include "./xcmathConfig.h"
namespace xcmath {
    class Symbol;
class XCMATH_API Fraction {
    public:
    Fraction() = default;
    ~Fraction() = default;

    virtual Fraction& operator+();
};
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_FRACTION_H