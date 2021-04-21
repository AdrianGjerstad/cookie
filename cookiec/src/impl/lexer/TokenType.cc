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

namespace cookie {

TokenType::TokenType(std::string repr) : repr_(repr) {
  // Nothing to do
}

const std::string TokenType::to_string() const {
  return repr_;
}

const TokenType TokenType::INT32 = TokenType("i32");    // signed i32 literal
const TokenType TokenType::UINT32 = TokenType("u32");   // unsigned i32 literal
const TokenType TokenType::INT64 = TokenType("i64");    // signed i64 literal
const TokenType TokenType::UINT64 = TokenType("u64");   // unsigned i64 literal
const TokenType TokenType::FLOAT32 = TokenType("f32");  // float literal
const TokenType TokenType::FLOAT64 = TokenType("f64");  // double literal

const TokenType TokenType::PLUS = TokenType("plus");        // +
const TokenType TokenType::MINUS = TokenType("minus");      // -
const TokenType TokenType::STAR = TokenType("star");        // *
const TokenType TokenType::SLASH = TokenType("slash");      // /
const TokenType TokenType::PERCENT = TokenType("percent");  // %

const TokenType TokenType::LEFT_PARENTHESIS = TokenType("lparen");   // (
const TokenType TokenType::RIGHT_PARENTHESIS = TokenType("rparen");  // )

}  // namespace cookie

