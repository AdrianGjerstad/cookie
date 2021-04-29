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

#ifndef COOKIEC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class FunctionCallNode: public Node {
 public:
  FunctionCallNode(const Token&, std::vector<std::shared_ptr<Node>>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token name_;
  std::vector<std::shared_ptr<Node>> args_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_FUNCTIONCALLNODE_H_

