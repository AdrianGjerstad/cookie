#ifndef COOKEIC_SRC_INCLUDE_AST_ARGUMENTLISTNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_ARGUMENTLISTNODE_H_

#include <string>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class ArgumentListNode: public Node {
 public:
  ArgumentListNode(std::vector<Token>, std::vector<Token>);

  virtual std::string to_string(int, bool) const;

 private:
  std::vector<Token> types_;
  std::vector<Token> names_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_ARGUMENTLISTNODE_H_

