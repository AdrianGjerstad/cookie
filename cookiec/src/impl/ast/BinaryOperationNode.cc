#include "../../include/ast/BinaryOperationNode.h"

#include <string>
#include <memory>

#include "../../include/ast/Node.h"
#include "../../include/lexer/Token.h"

namespace cookie {

BinaryOperationNode::BinaryOperationNode(
    std::shared_ptr<Node> left, const Token& operation,
    std::shared_ptr<Node> right) :
    left_(left), right_(right), operation_(operation) {
  // Nothing to do
}

std::string BinaryOperationNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[33m";

  res += "BinaryOperationNode";

  if (use_color) res += "\x1b[0m";

  res += "(\n";
  res += left_->to_string(depth + 2, use_color) + ",\n";

  if (use_color) res += "\x1b[32m";

  res += string_depth_pre_(depth + 2) + operation_.get_value();

  if (use_color) res += "\x1b[0m";

  res += ",\n";
  res += right_->to_string(depth + 2, use_color) + "\n";
  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

