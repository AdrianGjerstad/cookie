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

#include "../../include/ast/SymbolReferenceNode.h"

#include <string>

#include "../../include/lexer/Token.h"

namespace cookie {

SymbolReferenceNode::SymbolReferenceNode(
    const Token& token) :
    token_(token) {
  // Nothing to do
}

std::string SymbolReferenceNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[32m";
  res += "SymbolReferenceNode";
  if (use_color) res += "\x1b[0m";

  res += "(";

  if (use_color) res += "\x1b[34m";
  res += token_.to_string();
  if (use_color) res += "\x1b[0m";

  res += ")";

  return res;
}

}  // namespace cookie

