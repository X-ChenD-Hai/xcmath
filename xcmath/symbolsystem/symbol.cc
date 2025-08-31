#include "./symbol.h"
const std::string &xcmath::Symbol::name() const { return __name; }
xcmath::Symbol::Symbol(const std::string &name) : __name(name) {}
