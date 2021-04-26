#ifndef COOKEIC_SRC_INCLUDE_AST_SYMBOLREFERENCENODE_H_
#define COOKIEC_SRC_INCLUDE_AST_SYMBOLREFERENCENODE_H_

#include <string>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class SymbolReferenceNode: public Node {
 public:
  SymbolReferenceNode(const Token&);

  virtual std::string to_string(int, bool) const;

 private:
  const Token& token_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_SYMBOLREFERENCENODE_H_

