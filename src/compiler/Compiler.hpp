// src/compiler/Compiler.hpp
#pragma once

#include "Global.hpp"
#include "compiler/CompilerContext.hpp"
#include "compiler/CompilerOptions.hpp"
#include "trace/StackTrace.hpp"

namespace tea {

class Compiler {
 private:
  uptr<CompilerOptions> options_;
  uptr<CompilerContext> context_;
  uptr<StackTrace> stacktrace_;

 public:
  Compiler();
  ~Compiler();

  // Restrict copy
  Compiler(const Compiler&) = delete;
  Compiler& operator=(const Compiler&) = delete;

  // Main method
  int Run(int argc, char* argv[]);

  int Compile();
  bool Validate();

  void PrintVersion();
  void PrintHelp();

  void InitOptions(int argc, char* argv[]);
  void InitContext();
  void InitStackTrace();
};

}  // namespace tea