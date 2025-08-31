#ifndef XCMATH_SYMBOLSYSTEM_MONOMIAL_H
#define XCMATH_SYMBOLSYSTEM_MONOMIAL_H
#include <memory>
#include <vector>

#include "./constant.h"
#include "./xcmathConfig.h"

namespace xcmath {
class Symbol;
typedef std::vector<std::shared_ptr<Constant>> CoefficientPack;
typedef std::vector<std::shared_ptr<Symbol>> VariablePack;
class XCMATH_API Monomial {
   private:
    CoefficientPack __coefficient_pack;
    VariablePack __variable_pack;

   public:
    Monomial(const CoefficientPack& ceoffient_pack,
             const VariablePack& variable_pack);
    ~Monomial() = default;

   public:
    Monomial operator*(const Monomial& o);
    Monomial operator*(const Symbol& o);
};
};  // namespace xcmath

#endif  // XCMATH_SYMBOLSYSTEM_MONOMIAL_H