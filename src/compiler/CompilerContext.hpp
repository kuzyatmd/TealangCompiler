// CompilerContext.hpp
#pragma once

#include "Global.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "reader/Reader.hpp"

namespace tea {

class CompilerContext {
 public:
  Reader reader;
  Parser parser;
  Lexer lexer;

  CompilerContext();
  ~CompilerContext();

  static uptr<CompilerContext> Default();
};

}  // namespace tea