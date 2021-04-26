#ifndef COOKEIC_SRC_INCLUDE_AST_CODEBODYNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_CODEBODYNODE_H_

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class CodeBodyNode: public Node {
 public:
  CodeBodyNode();

  virtual std::string to_string(int, bool) const;

  void push_back(std::shared_ptr<Node>);

 private:
  std::vector<std::shared_ptr<Node>> statements_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_CODEBODYNODE_H_

