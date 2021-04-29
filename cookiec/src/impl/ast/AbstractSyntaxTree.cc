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

#include "../../include/ast/AbstractSyntaxTree.h"

#include <string>
#include <memory>
#include <vector>

#include "../../include/lexer/Token.h"

namespace cookie {

AbstractSyntaxTree::AbstractSyntaxTree() {
  // Nothing to do
}

void AbstractSyntaxTree::push_function(std::shared_ptr<Node> func) {
  functions_.push_back(func);
}

void AbstractSyntaxTree::push_global(std::shared_ptr<Node> global) {
  globals_.push_back(global);
}

const std::vector<std::shared_ptr<Node>>& AbstractSyntaxTree::functions()
    const {
  return functions_;
}

const std::vector<std::shared_ptr<Node>>& AbstractSyntaxTree::globals() const {
  return globals_;
}

std::string AbstractSyntaxTree::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[36m";
  res += "AbstractSyntaxTree";
  if (use_color) res += "\x1b[0m";
  res += "(\n";

  res += string_depth_pre_(depth + 2);
  if (use_color) res += "\x1b[34m";
  res += "FUNCTIONS";
  if (use_color) res += "\x1b[0m";
  res += " {\n";

  for (unsigned int i = 0; i < functions_.size(); ++i) {
    res += functions_[i]->to_string(depth + 4, use_color);

    if (i + 1 < functions_.size()) {
      res += ",\n";
    } else {
      res += "\n";
    }
  }

  res += string_depth_pre_(depth + 2) + "},\n";

  res += string_depth_pre_(depth + 2);
  if (use_color) res += "\x1b[34m";
  res += "GLOBALS";
  if (use_color) res += "\x1b[0m";
  res += " {\n";

  for (unsigned int i = 0; i < globals_.size(); ++i) {
    res += globals_[i]->to_string(depth + 4, use_color);

    if (i + 1 < globals_.size()) {
      res += ",\n";
    } else {
      res += "\n";
    }
  }

  res += string_depth_pre_(depth + 2) + "}\n";
  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

