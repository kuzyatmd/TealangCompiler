// parser/Parser.cpp
#include "parser/Parser.hpp"

#include "tokens/Token.hpp"

namespace tea {

Parser::Parser() {
}
Parser::~Parser() {
}

void Parser::Process(std::vector<Token> tokens) {
  int i = 0;
  for (; i < tokens.size(); i++) {
    auto token = tokens[i];

    switch (token.type) {
      // May be splitted type
      case TokenType::Number:
        break;

      case TokenType::Lexeme:
        break;

      // Format Types
      case TokenType::NewLine:
      case TokenType::Space:
      case TokenType::Tab:

        break;

      // String
      case TokenType::Quote:
        break;
      case TokenType::DQuote:
        break;

      default:

        break;
    }
  }
}

}  // namespace tea