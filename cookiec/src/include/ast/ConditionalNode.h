#ifndef COOKEIC_SRC_INCLUDE_AST_CONDITIONALNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_CONDITIONALNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class ConditionalNode: public Node {
 public:
  ConditionalNode(std::shared_ptr<Node>, std::shared_ptr<Node>,
      std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  std::shared_ptr<Node> expression_;
  std::shared_ptr<Node> body_;
  std::shared_ptr<Node> elsebody_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_CONDITIONALNODE_H_

