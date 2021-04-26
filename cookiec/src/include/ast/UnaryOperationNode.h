#ifndef COOKEIC_SRC_INCLUDE_AST_UNARYOPERATIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_UNARYOPERATIONNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class UnaryOperationNode: public Node {
 public:
  UnaryOperationNode(const Token&, std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token& operation_;
  std::shared_ptr<Node> child_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_UNARYOPERATIONNODE_H_

