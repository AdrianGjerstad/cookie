#ifndef COOKEIC_SRC_INCLUDE_AST_FORLOOPNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_FORLOOPNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class ForLoopNode: public Node {
 public:
  ForLoopNode(std::shared_ptr<Node>, std::shared_ptr<Node>,
      std::shared_ptr<Node>, std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  std::shared_ptr<Node> init_expr_;
  std::shared_ptr<Node> check_expr_;
  std::shared_ptr<Node> post_expr_;
  std::shared_ptr<Node> body_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_FORLOOPNODE_H_

