#include "../../include/ast/SymbolReferenceNode.h"

#include <string>

#include "../../include/lexer/Token.h"

namespace cookie {

SymbolReferenceNode::SymbolReferenceNode(
    const Token& token) :
    token_(token) {
  // Nothing to do
}

std::string SymbolReferenceNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "SymbolReferenceNode";
  if (use_color) res += "\x1b[0m";

  res += "(";

  if (use_color) res += "\x1b[34m";
  res += token_.to_string();
  if (use_color) res += "\x1b[0m";

  res += ")";

  return res;
}

}  // namespace cookie

