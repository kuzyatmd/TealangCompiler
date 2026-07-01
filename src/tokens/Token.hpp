// tokens/Token.hpp
#pragma once
#include <cstdint>

#include "tokens/TokenType.hpp"

namespace tea {

// 8 bytes
struct Token {
  const TokenType type;
  const uint32_t offset;
  const uint16_t length;
};

}  // namespace tea