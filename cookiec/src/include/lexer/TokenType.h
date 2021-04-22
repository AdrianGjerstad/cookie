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

#ifndef COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_
#define COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_

#include <string>

namespace cookie {

class TokenType {
 public:
  explicit TokenType(std::string);

  const std::string to_string() const;

  static const TokenType INT32;    // signed i32 literal
  static const TokenType UINT32;   // unsigned i32 literal
  static const TokenType INT64;    // signed i64 literal
  static const TokenType UINT64;   // unsigned i64 literal
  static const TokenType FLOAT32;  // float literal
  static const TokenType FLOAT64;  // double literal

  static const TokenType PLUS;     // +
  static const TokenType MINUS;    // -
  static const TokenType STAR;     // *
  static const TokenType SLASH;    // /
  static const TokenType PERCENT;  // %

  static const TokenType LEFT_PARENTHESIS;   // (
  static const TokenType RIGHT_PARENTHESIS;  // )

  static const TokenType END_OF_FILE;
 private:
  std::string repr_;
};

bool operator ==(const TokenType&, const TokenType&);

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_

