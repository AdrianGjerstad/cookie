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

#include "../../include/cli/CommandLineInterface.h"

#include <string>
#include <iostream>

#include "../../include/structs/CommandLineArguments.h"

cookie::CommandLineInterface::CommandLineInterface() {
  // Nothing to do
}

cookie::CommandLineArguments cookie::CommandLineInterface::run(
    int argc,
    char** argv) {
  cookie::CommandLineArguments args;

  args.argc = argc;
  args.argv = argv;

  bool stop_processing_flags = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    unsigned int size = arg.size();

    if (!stop_processing_flags && size > 0 && arg[0] == '-') {
      // Argument is a flag

      if (size == 2 && arg[1] == '-') {
        // Stop processing arguments as potential flags
        stop_processing_flags = true;
      } else if (size > 1 && arg[1] == '-') {
        // Argument is a long flag
        if (arg.substr(0, 8) == "--output") {
          // Output file being specified
          if (size > 8 && arg[8] == '=') {
            // Using GNU --abc=foo syntax
            if (args.output == "") {
              args.output = arg.substr(9);
              if (args.output == "-") {
                args.terminal_output = true;
              }
            } else {
              args.errors.push_back("cannot specify multiple output files");
            }
          } else if (size > 8) {
            args.errors.push_back(
                std::string("unrecognized argument '") + arg + "'");
          } else {
            // Using GNU --abc foo syntax
            ++i;
            if (i == argc) {
              args.errors.push_back("expected file name after '--output'");
              break;
            }

            std::string field = argv[i];
            if (args.output == "") {
              args.output = field;
              if (field == "-") {
                args.terminal_output = true;
              }
            } else {
              args.errors.push_back("cannot specify multiple output files");
            }
          }
        } else if (arg.substr(0, 9) == "--verbose") {
          // Specifying a verbosity level, or just that things should be
          // verbose.
          if (size > 9 && arg[9] == '=') {
            // Using GNU --abc=foo syntax
            std::string v = arg.substr(10);
            if (v == "0") args.verbosity_level = 0;
            else if (v == "1") args.verbosity_level = 1;
            else if (v == "2") args.verbosity_level = 2;
            else if (v == "3") args.verbosity_level = 3;
            else
              args.errors.push_back(
                    std::string("unrecognized verbosity level: '") + v + "'");
          } else if (size > 9) {
            args.errors.push_back(
                std::string("unrecognized argument '") + arg + "'");
          } else {
            // Using GNU --abc foo syntax
            ++i;
            if (argc == i) {
              // the argument is just --verbose at the end.
              args.verbosity_level = 1;
              break;
            }

            std::string v = argv[i];
            if (v == "0") {
              args.verbosity_level = 0;
            } else if (v == "1") {
              args.verbosity_level = 1;
            } else if (v == "2") {
              args.verbosity_level = 2;
            } else if (v == "3") {
              args.verbosity_level = 3;
            } else {
              args.verbosity_level = 1;
              --i;
            }
          }
        } else if (arg == "--help") {
          args.print_help = true;
        } else if (arg == "--brief") {
          args.verbosity_level = 0;
        } else {
          args.errors.push_back(
              std::string("unrecognized argument '") + arg + "'");
        }
      } else if (size > 1) {
        // Argument is a short flag
        if (arg[1] == 'o') {
          // Output file being specified
          if (size > 2 && arg[2] == '=') {
            // Using GNU -a=foo syntax
            if (args.output == "") {
              args.output = arg.substr(3);
              if (args.output == "-") {
                args.terminal_output = true;
              }
            } else {
              args.errors.push_back("cannot specify multiple output files");
            }
          } else if (size > 2) {
            // Using GNU -afoo syntax
            if (args.output == "") {
              args.output = arg.substr(2);
              if (args.output == "-") {
                args.terminal_output = true;
              }
            } else {
              args.errors.push_back("cannot specify multiple output files");
            }
          } else {
            // Using GNU -a foo syntax
            ++i;
            if (i == argc) {
              args.errors.push_back("expected file name after '-o'");
              break;
            }

            std::string field = argv[i];
            if (args.output == "") {
              args.output = field;
              if (field == "-") {
                args.terminal_output = true;
              }
            } else {
              args.errors.push_back("cannot specify multiple output files");
            }
          }
        } else if (arg[1] == 's') {
          args.halt_before_assembly = true;
        } else if (arg[1] == 'O') {
          // Specifying optimization level
          if (size > 2 && arg[2] == '=') {
            // Using GNU -a=foo syntax
            if (size == 3) {
              args.errors.push_back("unrecognized optimization level: ''");
            } else {
              std::string O = arg.substr(3);
              if (O == "0") args.optimization_level = 0;
              else if (O == "1") args.optimization_level = 1;
              else if (O == "2") args.optimization_level = 2;
              else if (O == "3") args.optimization_level = 3;
              else
                args.errors.push_back(
                    std::string("unrecognized optimization level: '") + O +
                    "'");
            }
          } else if (size > 2) {
            // Using GNU -afoo syntax
            std::string O = arg.substr(2);
            if (O == "0") args.optimization_level = 0;
            else if (O == "1") args.optimization_level = 1;
            else if (O == "2") args.optimization_level = 2;
            else if (O == "3") args.optimization_level = 3;
            else
              args.errors.push_back(
                  std::string("unrecognized optimization level: '") + O + "'");
          } else {
            // Using GNU -a foo syntax
            ++i;
            if (argc == i) {
              args.errors.push_back("expected optimization level after '-O'");
              break;
            }

            std::string O = argv[i];
            if (O == "0") args.optimization_level = 0;
            else if (O == "1") args.optimization_level = 1;
            else if (O == "2") args.optimization_level = 2;
            else if (O == "3") args.optimization_level = 3;
            else
              args.errors.push_back(
                  std::string("unrecognized optimization level: '") + O + "'");
          }
        } else if (arg[1] == 'v') {
          // Specifying a verbosity level, or just that things should be
          // verbose.
          if (size > 2 && arg[2] == '=') {
            // Using GNU -a=foo syntax
            std::string v = arg.substr(3);
            if (v == "0") args.verbosity_level = 0;
            else if (v == "1") args.verbosity_level = 1;
            else if (v == "2") args.verbosity_level = 2;
            else if (v == "3") args.verbosity_level = 3;
            else
              args.errors.push_back(
                  std::string("unrecognized verbosity level: '") + v + "'");
          } else if (size > 2) {
            // Using GNU -afoo syntax
            std::string v = arg.substr(2);
            if (v == "0") args.verbosity_level = 0;
            else if (v == "1") args.verbosity_level = 1;
            else if (v == "2") args.verbosity_level = 2;
            else if (v == "3") args.verbosity_level = 3;
            else
              args.errors.push_back(
                  std::string("unrecognized verbosity level: '") + v + "'");
          } else {
            // Using GNU -a foo syntax
            ++i;
            if (argc == i) {
              // the argument is just -v at the end.
              args.verbosity_level = 1;
              break;
            }

            std::string v = argv[i];
            if (v == "0") {
              args.verbosity_level = 0;
            } else if (v == "1") {
              args.verbosity_level = 1;
            } else if (v == "2") {
              args.verbosity_level = 2;
            } else if (v == "3") {
              args.verbosity_level = 3;
            } else {
              args.verbosity_level = 1;
              --i;
            }
          }
        } else if (arg[1] == 'h') {
          args.print_help = true;
        } else {
          args.errors.push_back(
              std::string("unrecognized argument '") + arg + "'");
        }
      } else {
        // False alarm; argument is actually just a dash
        if (args.input == "") {
          args.input = "-";
          args.terminal_input = true;
        } else {
          args.errors.push_back("multiple input file arguments specified");
        }
      }
    } else {
      // Argument is a field not related to a flag
      if (args.input == "") {
        args.input = arg;
      } else {
        args.errors.push_back("multiple input file arguments specified");
      }
    }
  }

  if (args.input == "" && !args.print_help) {
    // An input file was never specified
    args.errors.push_back("input file not specified");
  }

  if (args.output == "") {
    if (args.halt_before_assembly) {
      args.output = "a.out.wat";
    } else {
      args.output = "a.out.wasm";
    }
  }

  return args;
}

void cookie::CommandLineInterface::print_errors(
    cookie::CommandLineArguments args) {
  std::cerr << "Usage: " << args.argv[0] << " [OPTIONS] FILE\n"
"\n"
"    Compile Cookie code to a WebAssembly module.\n"
"\n"
"Options:\n"
"    -h, --help     Display this message and exit\n"
"    -o, --output   Specify an output file to write to\n"
"    -s             Output text format of module\n"
"    -O             Specify an amount of optimization to apply\n"
"    -v, --verbose  Specify the verbosity of the compiler's output\n"
"    -W             Subdue/ignore a warning type\n"
"    -E             Elevate the severity of a warning to an error\n"
"    --brief        Disable verbose output\n"
"\n"
"Please consider contributing to the project at the link below:\n"
"  https://github.com/AdrianGjerstad/cookie\n"
"Thank you!" << std::endl;

  for (unsigned int i = 0; i < args.errors.size(); ++i) {
    std::cerr << "\x1b[1m" << args.argv[0] << ": \x1b[31merror: \x1b[0m" <<
        args.errors[i] << std::endl;
  }
}

