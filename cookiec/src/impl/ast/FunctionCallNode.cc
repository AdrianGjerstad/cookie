#include "../../include/ast/FunctionCallNode.h"

#include <string>
#include <vector>

#include "../../include/lexer/Token.h"

namespace cookie {

FunctionCallNode::FunctionCallNode(
    const Token& name, std::vector<std::shared_ptr<Node>> args) :
    name_(name), args_(args) {
  // Nothing to do
}

std::string FunctionCallNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "FunctionCallNode";
  if (use_color) res += "\x1b[0m";

  res += "(";

  if (use_color) res += "\x1b[34m";
  res += name_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",\n";

  for (unsigned int i = 0; i < args_.size(); ++i) {
    res += args_[i]->to_string(depth + 2, use_color);

    if (i + 1 < args_.size()) res += ",\n";
    else res += "\n";
  }

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

