// reader/Reader.hpp
#pragma once

#include <fstream>
#include <string_view>

#include "tokens/Token.hpp"

namespace tea {

class Reader {
 public:
  static constexpr size_t BUFFER_SIZE = 4096;

  Reader();
  ~Reader();
  void SetFile(std::string_view file);
  void Open();
  void Close();
  void Reset();
  std::string_view Read();
  std::string ReadLexeme(Token token);

 private:
  char buffer_[BUFFER_SIZE];
  std::string_view file_;
  int charCount;

  std::ifstream ifs_;
};

}  // namespace tea