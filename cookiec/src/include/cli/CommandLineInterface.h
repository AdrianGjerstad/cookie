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

#ifndef COOKIEC_SRC_INCLUDE_CLI_COMMANDLINEINTERFACE_H_
#define COOKIEC_SRC_INCLUDE_CLI_COMMANDLINEINTERFACE_H_

#include "../structs/CommandLineArguments.h"

namespace cookie {

class CommandLineInterface {
 public:
  CommandLineInterface();

  CommandLineArguments run(int, char**);
  void print_errors(CommandLineArguments);
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_CLI_COMMANDLINEINTERFACE_H_

