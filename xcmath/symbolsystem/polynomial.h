#pragma once
#ifndef XCMATH_SYMBOLSYSTEM_POLYNOMIAL_H
#define XCMATH_SYMBOLSYSTEM_POLYNOMIAL_H
#include <vector>

#include "./ops/ops.h"
#include "./xcmathConfig.h"
namespace xcmath {
    class Symbol;
class XCMATH_API Polynomial {
    public:
    Polynomial() = default;
    ~Polynomial() = default;

    virtual Polynomial& operator+();
};
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_POLYNOMIAL_H