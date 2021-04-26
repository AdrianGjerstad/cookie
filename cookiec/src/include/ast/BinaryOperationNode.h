#ifndef COOKEIC_SRC_INCLUDE_AST_BINARYOPERATIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_BINARYOPERATIONNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class BinaryOperationNode: public Node {
 public:
  BinaryOperationNode(std::shared_ptr<Node>, const Token&, std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  std::shared_ptr<Node> left_;
  std::shared_ptr<Node> right_;
  const Token& operation_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_BINARYOPERATIONNODE_H_

