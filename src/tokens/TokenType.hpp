// tokens/TokenType.hpp
#pragma once
#include <cstdint>
namespace tea {

enum class TokenType : uint8_t {
  // ASCII (<=127)
  LParen = '(',     // 40
  RParen = ')',     // 41
  LBrace = '{',     // 123
  RBrace = '}',     // 125
  LBracket = '[',   // 91
  RBracket = ']',   // 93
  Comma = ',',      // 44
  Semicolon = ';',  // 59
  Colon = ':',      // 58
  Dot = '.',        // 46

  Plus = '+',     // 43
  Minus = '-',    // 45
  Star = '*',     // 42
  Slash = '/',    // 47
  Percent = '%',  // 37
  Equal = '=',    // 61
  Less = '<',     // 60
  Greater = '>',  // 62
  Not = '!',      // 33

  Quote = '\'',
  DQuote = '\"',

  Space = ' ',
  Tab = '\t',
  NewLine = '\n',

  // Non-ASCII (>= 128)
  Lexeme = 128,
  Number = 129,
  Unknown,
};

}  // namespace tea