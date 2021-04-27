#include "../../include/ast/ConditionalNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

ConditionalNode::ConditionalNode(
    std::shared_ptr<Node> expression,
    std::shared_ptr<Node> body,
    std::shared_ptr<Node> elsebody) :
    expression_(expression), body_(body), elsebody_(elsebody) {
  type(Node::CONDITIONAL);
}

std::string ConditionalNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ConditionalNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  res += expression_->to_string(depth + 2, use_color) + ",\n";
  res += body_->to_string(depth + 2, use_color) + ",\n";
  res += elsebody_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

