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

#include "../../include/ast/ReturnNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

ReturnNode::ReturnNode(std::shared_ptr<Node> expr) : expr_(expr) {
  // Nothing to do
}

std::string ReturnNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "ReturnNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";

  res += expr_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

