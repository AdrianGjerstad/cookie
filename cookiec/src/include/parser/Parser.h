// Copyright 2021 Adrian Gjerstad
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
  ParserResult conditional_(const std::vector<Token>*, unsigned int*) const;
  ParserResult loop_(const std::vector<Token>*, unsigned int*) const;
  ParserResult expression_(const std::vector<Token>*, unsigned int*) const;
  ParserResult condexpr_(const std::vector<Token>*, unsigned int*) const;
  ParserResult bitexpr_(const std::vector<Token>*, unsigned int*) const;
  ParserResult bitshexpr_(const std::vector<Token>*, unsigned int*) const;
  ParserResult arithexpr_(const std::vector<Token>*, unsigned int*) const;
  ParserResult term_(const std::vector<Token>*, unsigned int*) const;
  ParserResult factor_(const std::vector<Token>*, unsigned int*) const;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_PARSER_PARSER_H_

