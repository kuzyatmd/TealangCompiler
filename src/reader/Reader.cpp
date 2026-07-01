// reader/Reader.cpp
#include "reader/Reader.hpp"

#include <filesystem>
#include <fstream>
#include <string_view>

#include "Global.hpp"
#include "tokens/Token.hpp"

namespace tea {

Reader::Reader() {
  DEBUG("Init");
}
Reader::~Reader() {
  DEBUG("Delete");
  if (ifs_.is_open()) {
    ifs_.close();
  }
}

// May not be absolute path!
void Reader::SetFile(std::string_view file) {
  file_ = file;
}

void Reader::Open() {
  std::string filepath = std::filesystem::absolute(file_);
  Info(filepath, " will be opened\n");
  ifs_.open(filepath, std::ios::binary);
}

void Reader::Close() {
  ifs_.close();
}

void Reader::Reset() {
  ifs_.clear();
}
std::string Reader::ReadLexeme(Token token) {
  // ifs_.clear();
  ifs_.seekg(token.offset);

  ifs_.read(this->buffer_, token.length);

  std::string result(this->buffer_, token.length);

  return result;
}

std::string_view Reader::Read() {
  this->ifs_.read(this->buffer_, BUFFER_SIZE);
  return {this->buffer_, static_cast<size_t>(this->ifs_.gcount())};
}

}  // namespace tea