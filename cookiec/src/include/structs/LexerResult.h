#ifndef COOKIEC_SRC_INCLUDE_STRUCTS_LEXERRESULT_H_
#define COOKIEC_SRC_INCLUDE_STRUCTS_LEXERRESULT_H_

#include <vector>

#include "../lexer/Token.h"
#include "../errors/Error.h"

namespace cookie {

struct LexerResult {
  std::vector<Token> tokens;
  std::vector<Error> errors;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_STRUCTS_LEXERRESULT_H_

