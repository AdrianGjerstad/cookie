#include "../../include/ast/Node.h"

#include <string>

namespace cookie {

Node::Node() {
  // Nothing to do
}

unsigned int Node::type() const {
  return type_;
}

void Node::type(unsigned int x) {
  type_ = x;
}

std::string Node::to_string(int depth, bool use_color) const {
  // Stub method for children of this class
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[31m";
  res += "Node()";
  if (use_color) res += "\x1b[0m";
  return res;
}

std::string Node::string_depth_pre_(int depth) const {
  return std::string(depth, ' ');
}

const unsigned int Node::ABSTRACT_SYNTAX_TREE = 1;
const unsigned int Node::ARGUMENT_LIST = 2;
const unsigned int Node::BINARY_OPERATION = 3;
const unsigned int Node::CODE_BODY = 4;
const unsigned int Node::FUNCTION = 5;
const unsigned int Node::GLOBAL_DEFINITION = 6;
const unsigned int Node::LITERAL = 7;
const unsigned int Node::NO_OPERATION = 8;
const unsigned int Node::RETURN = 9;
const unsigned int Node::SYMBOL_DEFINITION = 10;
const unsigned int Node::SYMBOL_REFERENCE = 11;
const unsigned int Node::UNARY_OPERATION = 12;

}  // namespace cookie

