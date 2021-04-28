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

#ifndef COOKIEC_SRC_INCLUDE_AST_GLOBALDEFINITIONNODE_H_
#define COOKIEC_SRC_INCLUDE_AST_GLOBALDEFINITIONNODE_H_

#include <string>
#include <memory>

#include "Node.h"
#include "../lexer/Token.h"

namespace cookie {

class GlobalDefinitionNode: public Node {
 public:
  GlobalDefinitionNode(const Token&, const Token&, const Token&, const Token&,
      std::shared_ptr<Node>);

  virtual std::string to_string(int, bool) const;

 private:
  const Token export_token_;
  const Token is_const_;
  const Token type_;
  const Token name_;
  std::shared_ptr<Node> expr_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_AST_GLOBALDEFINITIONNODE_H_

