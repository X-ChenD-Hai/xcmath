#ifndef XCMATH_SYMBOLSYSTEM_EXPRESSION_H
#define XCMATH_SYMBOLSYSTEM_EXPRESSION_H
#include <vector>

#include "./ops/ops.h"
#include "./xcmathConfig.h"
namespace xcmath {
    class Symbol;
class XCMATH_API Expression {
    public:
    Expression() = default;
    ~Expression() = default;

    virtual Expression& operator+();
};
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_EXPRESSION_H