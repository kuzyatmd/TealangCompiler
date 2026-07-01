// lexer/Lexer.hpp
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "tokens/Token.hpp"

namespace tea {

class Lexer {
 public:
  Lexer();
  ~Lexer();

  void Process(std::string_view buf);
  void Reset();
  void Close();
  std::vector<Token> GetTokens();

 private:
  std::string last_data;
  size_t start_offset;
  std::vector<Token> tokens_;
};
}  // namespace tea