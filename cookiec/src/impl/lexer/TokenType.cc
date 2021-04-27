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

#include "../../include/lexer/TokenType.h"

#include <string>
#include <iostream>

namespace cookie {

TokenType::TokenType(std::string repr) : repr_(repr) {
  // Nothing to do
}

const std::string TokenType::to_string() const {
  return repr_;
}

const TokenType TokenType::INT32 = TokenType("i32");     // signed i32 literal
const TokenType TokenType::UINT32 = TokenType("u32");    // unsigned i32 literal
const TokenType TokenType::INT64 = TokenType("i64");     // signed i64 literal
const TokenType TokenType::UINT64 = TokenType("u64");    // unsigned i64 literal
const TokenType TokenType::FLOAT32 = TokenType("f32");   // float literal
const TokenType TokenType::FLOAT64 = TokenType("f64");   // double literal
const TokenType TokenType::BOOLEAN = TokenType("bool");  // boolean literal

const TokenType TokenType::PLUS = TokenType("plus");          // +
const TokenType TokenType::MINUS = TokenType("minus");        // -
const TokenType TokenType::STAR = TokenType("star");          // *
const TokenType TokenType::SLASH = TokenType("slash");        // /
const TokenType TokenType::PERCENT = TokenType("percent");    // %
const TokenType TokenType::AMPERSAND = TokenType("amp");      // &
const TokenType TokenType::PIPE = TokenType("pipe");          // |
const TokenType TokenType::CARET = TokenType("caret");        // ^
const TokenType TokenType::DOUBLE_LESS = TokenType("ll");     // <<
const TokenType TokenType::DOUBLE_GREATER = TokenType("rr");  // >>
const TokenType TokenType::TILDE = TokenType("tilde");        // ~

const TokenType TokenType::DOUBLE_EQUALS = TokenType("dubeq");      // ==
const TokenType TokenType::BANG_EQUALS = TokenType("bangeq");       // !=
const TokenType TokenType::LESS = TokenType("less");                // <
const TokenType TokenType::GREATER = TokenType("great");            // >
const TokenType TokenType::LESS_EQUALS = TokenType("leq");          // <=
const TokenType TokenType::GREATER_EQUALS = TokenType("geq");       // >=
const TokenType TokenType::DOUBLE_AMPERSAND = TokenType("dubamp");  // &&
const TokenType TokenType::DOUBLE_PIPE = TokenType("dubpipe");      // ||
const TokenType TokenType::DOUBLE_CARET = TokenType("dubcar");      // ^^
const TokenType TokenType::BANG = TokenType("bang");                // !

const TokenType TokenType::LEFT_PARENTHESIS = TokenType("lparen");   // (
const TokenType TokenType::RIGHT_PARENTHESIS = TokenType("rparen");  // )
const TokenType TokenType::LEFT_BRACE = TokenType("lbrace");         // {
const TokenType TokenType::RIGHT_BRACE = TokenType("rbrace");        // }
const TokenType TokenType::LEFT_BRACKET = TokenType("lbrack");       // [
const TokenType TokenType::RIGHT_BRACKET = TokenType("rbrack");      // ]

const TokenType TokenType::KW_DATA_TYPE = TokenType("kw:type");
const TokenType TokenType::KW_VOID = TokenType("kw:void");
const TokenType TokenType::KW_RETURN = TokenType("kw:ret");
const TokenType TokenType::KW_CONST = TokenType("kw:const");
const TokenType TokenType::KW_EXPORT = TokenType("kw:export");
const TokenType TokenType::KW_IF = TokenType("kw:if");
const TokenType TokenType::KW_ELSE = TokenType("kw:else");
const TokenType TokenType::KW_FOR = TokenType("kw:for");
const TokenType TokenType::KW_WHILE = TokenType("kw:while");
const TokenType TokenType::KW_DO = TokenType("kw:do");
const TokenType TokenType::IDENTIFIER = TokenType("ident");

const TokenType TokenType::EQUALS = TokenType("equals");  // =

const TokenType TokenType::SEMICOLON = TokenType("semicolon");  // ;
const TokenType TokenType::COMMA = TokenType("comma");          // ,

const TokenType TokenType::END_OF_FILE = TokenType("eof");

const TokenType TokenType::NULL_TOKEN = TokenType("nultok");

bool operator ==(const TokenType& a, const TokenType& b) {
  return a.to_string() == b.to_string();
}

bool operator !=(const TokenType& a, const TokenType& b) {
  return a.to_string() != b.to_string();
}

}  // namespace cookie

