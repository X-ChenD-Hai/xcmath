#ifndef XCMATH_SYMBOLSYSTEM_EXPRESSION_H
#define XCMATH_SYMBOLSYSTEM_EXPRESSION_H
#include <vector>

#include "./ops/ops.h"
#include "./symbol.h"
#include "./xcmathConfig.h"

namespace xcmath {
class XCMATH_API Expression {
    friend Expression operator+(const Symbol &sym1, const Symbol &sym2);

   protected:
    struct Node {
        union {
            ops::Ops *op;
            Symbol *sym;
        } v;
        Node(ops::Ops *op) { this->v.op = op; }
        Node(Symbol *sym) { this->v.sym = sym; }
    };
    std::vector<Expression> __children;
};

Expression XCMATH_API operator+(const Symbol &sym1, const Symbol &sym2);
// Expression XCMATH_API &operator+(Expression &exp, const Symbol &sym);
Expression XCMATH_API &operator+(const Symbol &sym, Expression &exp);
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_EXPRESSION_H