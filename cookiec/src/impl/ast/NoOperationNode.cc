#include "../../include/ast/NoOperationNode.h"

#include <string>

#include "../../include/lexer/Token.h"

namespace cookie {

NoOperationNode::NoOperationNode() {
  // Nothing to do
}

std::string NoOperationNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "NoOperationNode()";
  if (use_color) res += "\x1b[0m";

  return res;
}

}  // namespace cookie

