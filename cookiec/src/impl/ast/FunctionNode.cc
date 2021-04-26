#include "../../include/ast/FunctionNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

FunctionNode::FunctionNode(
    const Token& export_token,
    const Token& const_return,
    const Token& return_type,
    const Token& name,
    std::shared_ptr<Node> arglist,
    std::shared_ptr<Node> body) :
    export_token_(export_token), const_return_(const_return),
    return_type_(return_type), name_(name), arglist_(arglist), body_(body) {
  type(Node::FUNCTION);
}

std::string FunctionNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "FunctionNode";
  if (use_color) res += "\x1b[0m";
  res += "(";

  if (use_color) res += "\x1b[35m";
  res += export_token_.to_string();
  if (use_color) res += "\x1b[0m";
  res += "~\n";

  res += string_depth_pre_(depth + 2) + "Returns: ";
  if (use_color) res += "\x1b[34m";
  res += const_return_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",";
  if (use_color) res += "\x1b[34m";
  res += return_type_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",\n";

  res += string_depth_pre_(depth + 2) + "Name: ";
  if (use_color) res += "\x1b[34m";
  res += name_.to_string();
  if (use_color) res += "\x1b[0m";
  res += ",\n";

  res += arglist_->to_string(depth + 2, use_color) + ",\n";
  res += body_->to_string(depth + 2, use_color) + "\n";
  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

