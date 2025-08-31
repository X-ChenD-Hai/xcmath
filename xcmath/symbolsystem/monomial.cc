#include "./monomial.h" 
xcmath::Monomial::Monomial(const CoefficientPack& ceoffient_pack,
             const VariablePack& variable_pack)
        : __coefficient_pack(ceoffient_pack), __variable_pack(variable_pack) {};