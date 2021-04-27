#include "../../include/ast/ForLoopNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

ForLoopNode::ForLoopNode(
    std::shared_ptr<Node> init_expr,
    std::shared_ptr<Node> check_expr,
    std::shared_ptr<Node> post_expr,
    std::shared_ptr<Node> body) :
    init_expr_(init_expr), check_expr_(check_expr), post_expr_(post_expr),
    body_(body) {
  type(Node::FOR_LOOP);
}

std::string ForLoopNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ForLoopNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  res += init_expr_->to_string(depth + 2, use_color) + ",\n";
  res += check_expr_->to_string(depth + 2, use_color) + ",\n";
  res += post_expr_->to_string(depth + 2, use_color) + ",\n";
  res += body_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

