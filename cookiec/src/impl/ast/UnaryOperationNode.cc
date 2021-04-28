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

#include "../../include/ast/UnaryOperationNode.h"

#include <string>
#include <memory>

#include "../../include/ast/Node.h"
#include "../../include/lexer/Token.h"

namespace cookie {

UnaryOperationNode::UnaryOperationNode(
    const Token& operation, std::shared_ptr<Node> child) :
    operation_(operation), child_(child) {
  // Nothing to do
}

std::string UnaryOperationNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[33m";
  res += "UnaryOperationNode";
  if (use_color) res += "\x1b[0m";
  res += "(\n";

  if (use_color) res += "\x1b[32m";
  res += string_depth_pre_(depth + 2) + operation_.get_value();
  if (use_color) res += "\x1b[0m";
  res += ",\n";

  res += child_->to_string(depth + 2, use_color) + "\n";
  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

