#ifndef COOKEIC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class FunctionCallNode: public Node {
 public:
  FunctionCallNode(const Token&, std::vector<std::shared_ptr<Node>>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token name_;
  std::vector<std::shared_ptr<Node>> args_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_

