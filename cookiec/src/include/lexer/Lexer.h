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
  Token make_identifier_(Position*) const;

  Token make_lt_(Position*) const;
  Token make_gt_(Position*) const;
  Token make_equals_(Position*) const;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_LEXER_H_

