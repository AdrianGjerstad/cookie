#include "../../include/ast/SymbolDefinitionNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

SymbolDefinitionNode::SymbolDefinitionNode(
    const Token& is_const, const Token& type__, const Token& name,
    const Token& operation, std::shared_ptr<Node> expr) :
    is_const_(is_const), type_(type__), name_(name), operation_(operation),
    expr_(expr) {
  type(Node::SYMBOL_DEFINITION);
}

std::string SymbolDefinitionNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "SymbolDefinitionNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  res += string_depth_pre_(depth + 2);
  if (use_color) res += "\x1b[34m";
  res += name_.to_string();
  if (use_color) res += "\x1b[0m";
  res += " : ";

  if (use_color) res += "\x1b[34m";
  res += is_const_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",";
  if (use_color) res += "\x1b[34m";
  res += type_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",\n";
  res += string_depth_pre_(depth + 2);
  if (use_color) res += "\x1b[34m";
  res += operation_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",\n";

  res += expr_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

