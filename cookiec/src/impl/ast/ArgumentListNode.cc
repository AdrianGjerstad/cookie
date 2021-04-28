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

#include "../../include/ast/ArgumentListNode.h"

#include <string>
#include <vector>

#include "../../include/lexer/Token.h"

namespace cookie {

ArgumentListNode::ArgumentListNode(
    std::vector<Token> types, std::vector<Token> names) :
    types_(types), names_(names) {
  // Nothing to do
}

std::string ArgumentListNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ArgumentListNode";
  if (use_color) res += "\x1b[0m";
  res += "(\n";

  for (unsigned int i = 0; i < types_.size(); ++i) {
    res += string_depth_pre_(depth + 2);
    if (use_color) res += "\x1b[34m";
    res += names_[i].to_string();
    if (use_color) res += "\x1b[0m";
    res += " : ";

    if (use_color) res += "\x1b[34m";
    res += types_[i].to_string();
    if (use_color) res += "\x1b[0m";

    if (types_.size() > i + 1) {
      res += ",\n";
    } else {
      res += "\n";
    }
  }

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

