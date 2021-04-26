#ifndef COOKEIC_SRC_INCLUDE_AST_SYMBOLDEFINITIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_SYMBOLDEFINITIONNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class SymbolDefinitionNode: public Node {
 public:
  SymbolDefinitionNode(const Token&, const Token&, const Token&,
      std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token is_const_;
  const Token type_;
  const Token name_;
  std::shared_ptr<Node> expr_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_SYMBOLDEFINITIONNODE_H_

