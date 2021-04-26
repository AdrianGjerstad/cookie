#ifndef COOKIEC_SRC_INCLUDE_AST_NODE_H_
#define COOKIEC_SRC_INCLUDE_AST_NODE_H_

#include <string>

namespace cookie {

class Node {
 public:
  Node();

  virtual std::string to_string(int, bool) const;

  unsigned int type() const;
  void type(unsigned int);

  static const unsigned int ABSTRACT_SYNTAX_TREE;
  static const unsigned int ARGUMENT_LIST;
  static const unsigned int BINARY_OPERATION;
  static const unsigned int CODE_BODY;
  static const unsigned int FUNCTION;
  static const unsigned int GLOBAL_DEFINITION;
  static const unsigned int LITERAL;
  static const unsigned int NO_OPERATION;
  static const unsigned int RETURN;
  static const unsigned int SYMBOL_DEFINITION;
  static const unsigned int SYMBOL_REFERENCE;
  static const unsigned int UNARY_OPERATION;

 protected:
  std::string string_depth_pre_(int) const;
  unsigned int type_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_NODE_H_

