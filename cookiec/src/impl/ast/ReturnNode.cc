#include "../../include/ast/ReturnNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

ReturnNode::ReturnNode(std::shared_ptr<Node> expr) : expr_(expr) {
  // Nothing to do
}

std::string ReturnNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ReturnNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  res += expr_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

