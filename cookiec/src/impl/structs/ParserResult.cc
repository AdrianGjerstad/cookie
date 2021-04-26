#include "../../include/structs/ParserResult.h"

#include <memory>

#include "../../include/ast/Node.h"
#include "../../include/errors/Error.h"

namespace cookie {

std::shared_ptr<Node> ParserResult::use(ParserResult result) {
  for(unsigned int i = 0; i < result.errors.size(); ++i) {
    errors.push_back(result.errors[i]);
  }

  return result.tree;
}

ParserResult ParserResult::success(std::shared_ptr<Node> node) {
  tree = node;

  return (*this);
}

ParserResult ParserResult::failure(Error err) {
  errors.push_back(err);

  return (*this);
}

}  // namespace cookie

