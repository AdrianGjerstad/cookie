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

#ifndef COOKIEC_SRC_INCLUDE_STRUCTS_COMMANDLINEARGUMENTS_H_
#define COOKIEC_SRC_INCLUDE_STRUCTS_COMMANDLINEARGUMENTS_H_

#include <string>
#include <vector>
#include <unordered_map>

namespace cookie {

struct CommandLineArguments {
  std::vector<std::string> errors;

  int argc;
  char** argv;

  bool print_help = false;

  std::string input = "";
  std::string output = "";

  bool terminal_input = false;
  bool terminal_output = false;

  bool halt_before_assembly = false;

  int optimization_level = 1;
  int verbosity_level = 0;

  bool subdue_all_warnings = false;   // -Wall
  bool elevate_all_warnings = false;  // -Eall
  std::unordered_map<std::string, bool> subdue_warnings = {};   // -Wxyz
  std::unordered_map<std::string, bool> elevate_warnings = {};  // -Exyz
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_STRUCTS_COMMANDLINEARGUMENTS_H_

