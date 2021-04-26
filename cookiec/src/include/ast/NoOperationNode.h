#ifndef COOKEIC_SRC_INCLUDE_AST_NOOPERATIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_NOOPERATIONNODE_H_

#include <string>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class NoOperationNode: public Node {
 public:
  NoOperationNode();

  virtual std::string to_string(int, bool) const;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_NOOPERATIONNODE_H_

