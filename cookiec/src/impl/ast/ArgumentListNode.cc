#include "../../include/ast/ArgumentListNode.h"

#include <string>
#include <vector>

#include "../../include/lexer/Token.h"

namespace cookie {

ArgumentListNode::ArgumentListNode(
    std::vector<Token> types, std::vector<Token> names) :
    types_(types), names_(names) {
  // Nothing to do
}

std::string ArgumentListNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ArgumentListNode";
  if (use_color) res += "\x1b[0m";
  res += "(\n";

  for (unsigned int i = 0; i < types_.size(); ++i) {
    res += string_depth_pre_(depth + 2);
    if (use_color) res += "\x1b[34m";
    res += names_[i].to_string();
    if (use_color) res += "\x1b[0m";
    res += " : ";

    if (use_color) res += "\x1b[34m";
    res += types_[i].to_string();
    if (use_color) res += "\x1b[0m";

    if(types_.size() > i + 1) {
      res += ",\n";
    } else {
      res += "\n";
    }
  }

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

