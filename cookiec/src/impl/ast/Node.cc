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

#include "../../include/ast/Node.h"

#include <string>

namespace cookie {

Node::Node() {
  // Nothing to do
}

unsigned int Node::type() const {
  return type_;
}

void Node::type(unsigned int x) {
  type_ = x;
}

std::string Node::to_string(int depth, bool use_color) const {
  // Stub method for children of this class
  std::string res = string_depth_pre_(depth);

  if (use_color) res += "\x1b[31m";
  res += "Node()";
  if (use_color) res += "\x1b[0m";
  return res;
}

std::string Node::string_depth_pre_(int depth) const {
  return std::string(depth, ' ');
}

const unsigned int Node::ABSTRACT_SYNTAX_TREE = 1;
const unsigned int Node::ARGUMENT_LIST = 2;
const unsigned int Node::BINARY_OPERATION = 3;
const unsigned int Node::CODE_BODY = 4;
const unsigned int Node::CONDITIONAL = 5;
const unsigned int Node::FOR_LOOP = 6;
const unsigned int Node::FUNCTION = 7;
const unsigned int Node::FUNCTION_CALL = 8;
const unsigned int Node::GLOBAL_DEFINITION = 9;
const unsigned int Node::LITERAL = 10;
const unsigned int Node::NO_OPERATION = 11;
const unsigned int Node::RETURN = 12;
const unsigned int Node::SYMBOL_DEFINITION = 13;
const unsigned int Node::SYMBOL_REFERENCE = 14;
const unsigned int Node::UNARY_OPERATION = 15;
const unsigned int Node::WHILE_LOOP = 16;

}  // namespace cookie

