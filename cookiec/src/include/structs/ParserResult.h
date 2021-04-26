#ifndef COOKIEC_SRC_INCLUDE_PARSER_PARSERRESULT_H_
#define COOKIEC_SRC_INCLUDE_PARSER_PARSERRESULT_H_

#include <vector>
#include <memory>

#include "../ast/Node.h"
#include "../errors/Error.h"

namespace cookie {

struct ParserResult {
  std::vector<Error> errors;
  std::shared_ptr<Node> tree;

  std::shared_ptr<Node> use(ParserResult);

  ParserResult success(std::shared_ptr<Node>);
  ParserResult failure(Error);
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_PARSER_PARSERRESULT_H_

