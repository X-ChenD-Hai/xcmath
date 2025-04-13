#include "./symbol.h"
const std::string &xcmath::symbol::name() const { return __name; }
xcmath::symbol::symbol(const std::string &name) : __name(name) {}
