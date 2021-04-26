#ifndef COOKEIC_SRC_INCLUDE_AST_LITERALNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_LITERALNODE_H_

#include <string>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class LiteralNode: public Node {
 public:
  LiteralNode(const Token&);

  virtual std::string to_string(int, bool) const;

 private:
  const Token& token_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_LITERALNODE_H_

