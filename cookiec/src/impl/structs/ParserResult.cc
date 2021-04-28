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

#include "../../include/structs/ParserResult.h"

#include <memory>

#include "../../include/ast/Node.h"
#include "../../include/errors/Error.h"

namespace cookie {

std::shared_ptr<Node> ParserResult::use(ParserResult result) {
  for (unsigned int i = 0; i < result.errors.size(); ++i) {
    errors.push_back(result.errors[i]);
  }

  return result.tree;
}

ParserResult ParserResult::success(std::shared_ptr<Node> node) {
  tree = node;

  return (*this);
}

ParserResult ParserResult::failure(Error err) {
  errors.push_back(err);

  return (*this);
}

}  // namespace cookie

