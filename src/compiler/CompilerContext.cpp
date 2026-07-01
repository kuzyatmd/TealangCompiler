// compiler/CompilerContext.cpp
#include "compiler/CompilerContext.hpp"

#include "Global.hpp"

namespace tea {

CompilerContext::CompilerContext() {}
CompilerContext::~CompilerContext() {}

uptr<CompilerContext> CompilerContext::Default() {
  return std::make_unique<CompilerContext>();
}

} // namespace tea