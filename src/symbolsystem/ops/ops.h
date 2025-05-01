#ifndef XCMATH_SYMBOLS_OPS_H
#define XCMATH_SYMBOLS_OPS_H
#include "../xcmathConfig.h"
namespace xcmath::ops {
class XCMATH_API Ops {};

class XCMATH_API Add final : public Ops {
   public:
};
class XCMATH_API Sub final : public Ops {};
class XCMATH_API Mul final : public Ops {};
class XCMATH_API Div final : public Ops {};
class XCMATH_API Pow final : public Ops {};

};  // namespace xcmath::ops

#endif  // XCMATH_SYMBOLS_OPS_H