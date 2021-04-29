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

  // LITERAL TOKENS
  static const TokenType INT32;    // signed i32 literal
  static const TokenType UINT32;   // unsigned i32 literal
  static const TokenType INT64;    // signed i64 literal
  static const TokenType UINT64;   // unsigned i64 literal
  static const TokenType FLOAT32;  // float literal
  static const TokenType FLOAT64;  // double literal
  static const TokenType BOOLEAN;  // boolean literal

  // ARITHMETIC AND BITWISE TOKENS
  static const TokenType PLUS;            // +
  static const TokenType MINUS;           // -
  static const TokenType STAR;            // *
  static const TokenType SLASH;           // /
  static const TokenType PERCENT;         // %
  static const TokenType AMPERSAND;       // &
  static const TokenType PIPE;            // |
  static const TokenType CARET;           // ^
  static const TokenType DOUBLE_LESS;     // <<
  static const TokenType DOUBLE_GREATER;  // >>
  static const TokenType TILDE;           // ~

  // LOGICAL TOKENS
  static const TokenType DOUBLE_EQUALS;     // ==
  static const TokenType BANG_EQUALS;       // !=
  static const TokenType LESS;              // <
  static const TokenType GREATER;           // >
  static const TokenType LESS_EQUALS;       // <=
  static const TokenType GREATER_EQUALS;    // >=
  static const TokenType DOUBLE_AMPERSAND;  // &&
  static const TokenType DOUBLE_PIPE;       // ||
  static const TokenType DOUBLE_CARET;      // ^^
  static const TokenType BANG;              // !

  // BRACKET TOKENS
  static const TokenType LEFT_PARENTHESIS;   // (
  static const TokenType RIGHT_PARENTHESIS;  // )
  static const TokenType LEFT_BRACE;         // {
  static const TokenType RIGHT_BRACE;        // }
  static const TokenType LEFT_BRACKET;       // [
  static const TokenType RIGHT_BRACKET;      // ]

  // KEYWORDS
  static const TokenType KW_DATA_TYPE;  // i32, i64, bool, etc.
  static const TokenType KW_VOID;       // "void" literally (not as a string)
  static const TokenType KW_RETURN;     // return
  static const TokenType KW_CONST;      // const
  static const TokenType KW_EXPORT;     // export
  static const TokenType KW_IF;         // if
  static const TokenType KW_ELSE;       // else
  static const TokenType KW_FOR;        // for
  static const TokenType KW_WHILE;      // while
  static const TokenType KW_DO;         // do
  // VARIABLES, FUNCTIONS, GLOBALS, ETC.
  static const TokenType IDENTIFIER;    // Any variable name ever.

  // ASSIGNMENT TOKENS
  static const TokenType EQUALS;                 // =
  static const TokenType PLUS_EQUALS;            // +=
  static const TokenType MINUS_EQUALS;           // -=
  static const TokenType STAR_EQUALS;            // *=
  static const TokenType SLASH_EQUALS;           // /=
  static const TokenType PERCENT_EQUALS;         // %=
  static const TokenType AMPERSAND_EQUALS;       // &=
  static const TokenType PIPE_EQUALS;            // |=
  static const TokenType CARET_EQUALS;           // ^=
  static const TokenType DOUBLE_LESS_EQUALS;     // <<=
  static const TokenType DOUBLE_GREATER_EQUALS;  // >>=

  // SEPARATOR TOKENS
  static const TokenType SEMICOLON;  // ;
  static const TokenType COMMA;      // ,

  // EOF
  static const TokenType END_OF_FILE;

  // Token does not actually exist, but is generated in stages like the parser
  // for missing parameters names, for example.
  static const TokenType NULL_TOKEN;

 private:
  std::string repr_;
};

bool operator ==(const TokenType&, const TokenType&);
bool operator !=(const TokenType&, const TokenType&);

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_

