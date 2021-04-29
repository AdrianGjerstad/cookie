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

#include "../../include/ast/WhileLoopNode.h"

#include <string>
#include <memory>

#include "../../include/lexer/Token.h"

namespace cookie {

WhileLoopNode::WhileLoopNode(
    bool check_start,
    std::shared_ptr<Node> check_expr,
    std::shared_ptr<Node> body) :
    check_start_(check_start), check_expr_(check_expr), body_(body) {
  type(Node::WHILE_LOOP);
}

std::string WhileLoopNode::to_string(int depth, bool use_color) const {
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[35m";
  res += "WhileLoopNode";
  if (use_color) res += "\x1b[0m";

  res += "(\n";
  res += string_depth_pre_(depth + 2);

  if (use_color) res += "\x1b[31m";
  if (check_start_) {
    res += "WHILE";
  } else {
    res += "DO-WHILE";
  }

  if (use_color) res += "\x1b[0m";
  res += ",\n";

  res += check_expr_->to_string(depth + 2, use_color) + ",\n";
  res += body_->to_string(depth + 2, use_color) + "\n";

  res += string_depth_pre_(depth) + ")";

  return res;
}

}  // namespace cookie

