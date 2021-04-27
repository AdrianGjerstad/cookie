#ifndef COOKEIC_SRC_INCLUDE_AST_WHILELOOPNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_WHILELOOPNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class WhileLoopNode: public Node {
 public:
  WhileLoopNode(bool, std::shared_ptr<Node>, std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  bool check_start_;  // Should the check code be placed at the beginning or
                      // end of the code? AKA, is this a normal while loop, not
                      // a do-while loop?
  std::shared_ptr<Node> check_expr_;
  std::shared_ptr<Node> body_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_WHILELOOPNODE_H_

