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

#include <iostream>

// UTILITIES
#include "include/util/SourceCodePool.h"
#include "include/util/Filesystem.h"

// STAGE ONE: CLI
#include "include/cli/CommandLineInterface.h"
#include "include/structs/CommandLineArguments.h"

// STAGE TWO: LEXER
// #include "include/lexer/Lexer.h"

int main(int argc, char** argv) {
  cookie::CommandLineInterface cli;
  cookie::CommandLineArguments args = cli.run(argc, argv);

  if (args.errors.size() || args.print_help) {
    cli.print_errors(args);

    return 1;
  }

  cookie::SourceCodePool code_pool;

  if (args.terminal_input) {
    code_pool.add_cin("-");
    std::cout << *(code_pool.get("-")) << std::endl;
  } else {
    code_pool.add(args.input);
    std::cout << *(code_pool.get(args.input)) << std::endl;
  }

  return 0;
}

