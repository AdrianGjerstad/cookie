#include "../../include/ast/CodeBodyNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

CodeBodyNode::CodeBodyNode() {
  // Nothing to do
}

std::string CodeBodyNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "CodeBodyNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  for (unsigned int i = 0; i < statements_.size(); ++i) {
    res += statements_[i]->to_string(depth + 2, use_color);

    if (i + 1 != statements_.size()) {
      res += ",\n";
    } else {
      res += "\n";
    }
  }

  res += string_depth_pre_(depth) + ")";

  return res;
}

void CodeBodyNode::push_back(std::shared_ptr<Node> node) {
  statements_.push_back(node);
}

}  // namespace cookie

