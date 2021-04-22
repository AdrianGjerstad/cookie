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

#ifndef COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_
#define COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_

#include <string>

#include "../util/Position.h"

namespace cookie {

class Error {
 public:
  Error(Position, Position, std::string);

  std::string to_string(bool);

 protected:
  Position pstart_;
  Position pend_;
  std::string message_;
  std::string name_;

  Error(Position, Position, std::string, std::string);
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_

