#include "../../include/ast/GlobalDefinitionNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

GlobalDefinitionNode::GlobalDefinitionNode(
    const Token& export_token, const Token& is_const, const Token& type,
    const Token& name, std::shared_ptr<Node> expr) :
    export_token_(export_token), is_const_(is_const), type_(type), name_(name),
    expr_(expr) {
  // Nothing to do
}

std::string GlobalDefinitionNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "GlobalDefinitionNode";
  if (use_color) res += "\x1b[0m";

  res += "(";

  if (use_color) res += "\x1b[34m";
  res += export_token_.to_string();
  if (use_color) res += "\x1b[0m";
  res += "\n";

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

  res += expr_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

