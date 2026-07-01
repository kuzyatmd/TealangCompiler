// CompilerContext.hpp
#pragma once

#include "Global.hpp"

namespace tea {

class CompilerContext {
public:
  CompilerContext();
  ~CompilerContext();

  static uptr<CompilerContext> Default();
};

} // namespace tea