#ifndef COOKIEC_SRC_INCLUDE_PARSER_PARSER_H_
#define COOKIEC_SRC_INCLUDE_PARSER_PARSER_H_

#include <vector>

#include "../ast/Node.h"
#include "../lexer/Token.h"
#include "../structs/ParserResult.h"

namespace cookie {

class Parser {
 public:
  Parser();

  ParserResult parse(const std::vector<Token>*) const;

 private:
  const Token& advance_(const std::vector<Token>*, unsigned int*) const;

  ParserResult globalbody_(const std::vector<Token>*, unsigned int*) const;
  ParserResult globalitem_(const std::vector<Token>*, unsigned int*) const;
  ParserResult arglist_(const std::vector<Token>*, unsigned int*) const;
  ParserResult codebody_(const std::vector<Token>*, unsigned int*) const;
  ParserResult statement_(const std::vector<Token>*, unsigned int*) const;
  ParserResult expression_(const std::vector<Token>*, unsigned int*) const;
  ParserResult term_(const std::vector<Token>*, unsigned int*) const;
  ParserResult factor_(const std::vector<Token>*, unsigned int*) const;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_PARSER_PARSER_H_

