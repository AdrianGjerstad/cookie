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

#ifndef COOKIEC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_
#define COOKIEC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class AbstractSyntaxTree: public Node {
 public:
  AbstractSyntaxTree();

  virtual std::string to_string(int, bool) const;

  void push_function(std::shared_ptr<Node>);
  void push_global(std::shared_ptr<Node>);

  const std::vector<std::shared_ptr<Node>>& functions() const;
  const std::vector<std::shared_ptr<Node>>& globals() const;

 private:
  std::vector<std::shared_ptr<Node>> functions_;
  std::vector<std::shared_ptr<Node>> globals_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_ABSTRACTSYNTAXTREE_H_

