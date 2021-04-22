#ifndef COOKIEC_SRC_INCLUDE_LEXER_LEXER_H_
#define COOKIEC_SRC_INCLUDE_LEXER_LEXER_H_

#include <string>

#include "Token.h"
#include "TokenType.h"
#include "../util/Position.h"
#include "../util/SourceCodePool.h"
#include "../structs/LexerResult.h"

namespace cookie {

class Lexer {
 public:
  explicit Lexer(const SourceCodePool*);

  LexerResult lex(const std::string&) const;

 private:
  const SourceCodePool* pool_;

  Token make_number_(Position*) const;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_LEXER_H_

