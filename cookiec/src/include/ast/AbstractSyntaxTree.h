#ifndef COOKEIC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_
#define COOKIEC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class AbstractSyntaxTree: public Node {
 public:
  AbstractSyntaxTree();

  virtual std::string to_string(int, bool) const;

  void push_function(std::shared_ptr<Node>);
  void push_global(std::shared_ptr<Node>);

  const std::vector<std::shared_ptr<Node>>& functions() const;
  const std::vector<std::shared_ptr<Node>>& globals() const;

 private:
  std::vector<std::shared_ptr<Node>> functions_;
  std::vector<std::shared_ptr<Node>> globals_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_

