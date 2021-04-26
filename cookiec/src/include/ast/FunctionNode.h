#ifndef COOKEIC_SRC_INCLUDE_AST_FUNCTIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_FUNCTIONNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class FunctionNode: public Node {
 public:
  FunctionNode(const Token&, const Token&, const Token&, const Token&,
      std::shared_ptr<Node>, std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token export_token_;
  const Token const_return_;
  const Token return_type_;
  const Token name_;
  std::shared_ptr<Node> arglist_;
  std::shared_ptr<Node> body_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_FUNCTIONNODE_H_

