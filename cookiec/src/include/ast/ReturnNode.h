#ifndef COOKEIC_SRC_INCLUDE_AST_RETURNNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_RETURNNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class ReturnNode: public Node {
 public:
  ReturnNode(std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  std::shared_ptr<Node> expr_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_RETURNNODE_H_

