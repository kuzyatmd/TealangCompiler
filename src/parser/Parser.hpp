// parser/Parser.hpp

#include <vector>

#include "ast/SyntaxTree.hpp"
#include "tokens/Token.hpp"

namespace tea {

// vector<Token> -> SyntaxTree
class Parser {
 public:
  Parser();
  ~Parser();

  void Process(std::vector<Token> tokens_);

  SyntaxTree GetSyntaxTree();

 private:
  SyntaxTree st_;
};

}  // namespace tea