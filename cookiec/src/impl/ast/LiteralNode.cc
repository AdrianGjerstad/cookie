#include "../../include/ast/LiteralNode.h"

#include <string>

#include "../../include/lexer/Token.h"

namespace cookie {

LiteralNode::LiteralNode(
    const Token& token) :
    token_(token) {
  // Nothing to do
}

std::string LiteralNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "LiteralNode";
  if (use_color) res += "\x1b[0m";

  res += "(";

  if (use_color) res += "\x1b[34m";
  res += token_.to_string();
  if (use_color) res += "\x1b[0m";

  res += ")";

  return res;
}

}  // namespace cookie

