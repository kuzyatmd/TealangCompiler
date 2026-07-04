// lexer/Lexer.cpp
#include <lexer/Lexer.hpp>
#include <string>
#include <string_view>

#include "Global.hpp"
#include "tokens/Token.hpp"
#include "tokens/TokenType.hpp"

namespace tea {

Lexer::Lexer() {
  this->start_offset = 0;
  DEBUG("Init");
}
Lexer::~Lexer() {
  tokens_.clear();
  tokens_.shrink_to_fit();

  DEBUG("Delete");
}

// NOTE:
//  Lexer can produce tokens that are split for TokenType::Lexeme/Number.
//  Parser should automatically truncate them if no tokens found between them.
// EX:
//  tokens: ['Hel', 'lo'] -> ['Hello']
// but:
//  tokens: ['Hel', ' ', 'lo'] will be the same.
// so no TokenType::Lexeme/Number can be together
void Lexer::Process(std::string_view buf) {
  size_t i = 0;
  unsigned char ch;
  TokenType tokenType;

  for (; i < buf.size(); i++) {
    ch = static_cast<unsigned char>(buf[i]);

    // Symbol -> build lexeme and check if it is a keyword
    if (std::isalpha(ch)) {
      size_t start = i;

      while (++i < buf.size()) {
        unsigned char next = static_cast<unsigned char>(buf[i]);
        if (!std::isalnum(next) && next != '_')
          break;
      }

      uint16_t len = static_cast<uint16_t>(i - start);

      this->tokens_.push_back(
          {TokenType::Lexeme, static_cast<uint32_t>(this->start_offset + start),
           len});

      i--;
      continue;
    }
    // Number -> build number token
    else if (std::isdigit(ch)) {
      size_t start = i;

      while (++i < buf.size()) {
        unsigned char next = static_cast<unsigned char>(buf[i]);
        if (!std::isdigit(next) && next != 'x' && next != '_')
          break;
      }

      uint16_t len = static_cast<uint16_t>(i - start);
      this->tokens_.push_back(
          {TokenType::Number, static_cast<uint32_t>(this->start_offset + start),
           len});

      i--;
      continue;
    }
    // Keychar -> add token (raw ASCII conversion)
    else {
      tokenType = static_cast<TokenType>(ch);

      if (tokenType != TokenType::Unknown) {
        auto token =
            Token{tokenType, static_cast<uint32_t>(this->start_offset + i), 1};

        this->tokens_.push_back(token);
        continue;
      }
    }
  }

  this->start_offset += i;
}

std::vector<Token> Lexer::GetTokens() {
  return this->tokens_;
}

void Lexer::Reset() {
  start_offset = 0;
  last_data = "";
}

void Lexer::Close() {
  // delete this;
}

}  // namespace tea