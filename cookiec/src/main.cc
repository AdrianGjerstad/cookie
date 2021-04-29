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

#include <unistd.h>

#include <iostream>
#include <vector>
#include <cstdlib>

// UTILITIES
#include "include/util/SourceCodePool.h"
#include "include/util/Filesystem.h"
#include "include/errors/Error.h"

// STAGE ONE: CLI
#include "include/cli/CommandLineInterface.h"
#include "include/structs/CommandLineArguments.h"

// STAGE TWO: LEXER
#include "include/lexer/Token.h"
#include "include/lexer/Lexer.h"
#include "include/structs/LexerResult.h"

// STAGE THREE: PARSER
#include "include/parser/Parser.h"
#include "include/structs/ParserResult.h"
#include "include/ast/Node.h"

#include "include/ast/AbstractSyntaxTree.h"

int main(int argc, char** argv) {
  std::string VERBOSE_1 = "verbose[1]: ";
  std::string VERBOSE_2 = "verbose[2]: ";
  std::string VERBOSE_3 = "verbose[3]: ";
  bool USE_COLOR = false;

  if (isatty(2)) {
    // This process's stderr stream is attached to a terminal. It is safe to use
    // ANSI escape codes for coloring.

    VERBOSE_1 = "\x1b[34mverbose[1]:\x1b[0m ";
    VERBOSE_2 = "\x1b[34mverbose[2]:\x1b[0m ";
    VERBOSE_3 = "\x1b[34mverbose[3]:\x1b[0m ";
    USE_COLOR = true;
  }

  //////////////////////////////////////////////////////////////////////////////
  ////////////////////////// STAGE 1: COMMAND LINE I/O /////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  cookie::CommandLineInterface cli;
  cookie::CommandLineArguments args = cli.run(argc, argv);

  if (args.errors.size() || args.print_help) {
    cli.print_errors(args);

    return 1;
  }

  cookie::SourceCodePool code_pool;

  if (args.terminal_input) {
    code_pool.add_cin(args.input);
  } else {
    code_pool.add(args.input);
  }

  if (args.verbosity_level >= 1) {
    std::cerr << VERBOSE_1 << "File '" << args.input << "' read." << std::endl;
  }

  cookie::Lexer lexer(&code_pool);
  cookie::LexerResult lexer_out = lexer.lex(args.input);

  if (lexer_out.errors.size()) {
    if (args.verbosity_level >= 1) {
      std::cerr << VERBOSE_1 << "Encountered " << lexer_out.errors.size() <<
          " lexer errors" << std::endl;
    }

    if (USE_COLOR) {
      std::cerr << "\x1b[1;31mError in file '" << args.input << "':\x1b[0m" <<
          std::endl;
    } else {
      std::cerr << "Error in file '" << args.input << "':" << std::endl;
    }

    for (unsigned int i = 0; i < lexer_out.errors.size(); ++i) {
      std::cerr << lexer_out.errors[i].to_string(USE_COLOR) << std::endl;
    }

    return 1;
  }

  if (args.verbosity_level >= 1) {
    std::cerr << VERBOSE_1 << "Read " << lexer_out.tokens.size() << " tokens."
        << std::endl;

    if (args.verbosity_level >= 2) {
      if (USE_COLOR) {
        std::cerr << VERBOSE_2 << "\x1b[33mTOKEN LIST\x1b[0m {" << std::endl;
      } else {
        std::cerr << VERBOSE_2 << "TOKEN LIST {" << std::endl;
      }

      std::string line = VERBOSE_2 + "  ";

      for (unsigned int i = 0; i < lexer_out.tokens.size(); ++i) {
        if ((line.size() + lexer_out.tokens[i].to_string().size() + 2) -
            (USE_COLOR * 9) >= 80) {
          std::cerr << line << std::endl;
          line = VERBOSE_2 + "  ";
        }

        if (USE_COLOR) line += "\x1b[34m";
        line += lexer_out.tokens[i].to_string();
        if (USE_COLOR) line += "\x1b[0m";
        line += ", ";
      }

      if (line.size() > (VERBOSE_2).size() + 2) {
        std::cerr << line.substr(0, line.size()-2) << std::endl;
      }

      std::cerr << VERBOSE_2 << "}" << std::endl;
    }
  }

  cookie::Parser parser;
  cookie::ParserResult parser_out = parser.parse(&lexer_out.tokens);

  if (parser_out.errors.size()) {
    for (unsigned int i = 0; i < parser_out.errors.size(); ++i) {
      std::cerr << parser_out.errors[i].to_string(USE_COLOR) << std::endl;
    }

    return 1;
  }

  if (args.verbosity_level >= 1) {
    std::shared_ptr<cookie::AbstractSyntaxTree> tree =
        std::dynamic_pointer_cast<cookie::AbstractSyntaxTree>(parser_out.tree);

    std::cerr << VERBOSE_1 << "Parsing complete!" << std::endl;
    std::cerr << VERBOSE_1 << "Parsed " << tree->functions().size() <<
        " functions." << std::endl;
    std::cerr << VERBOSE_1 << "Parsed " << tree->globals().size() <<
        " globals." << std::endl;

    if (args.verbosity_level >= 2) {
      if (USE_COLOR) {
        std::cerr << VERBOSE_2 << "\x1b[33mABSTRACT SYNTAX TREE\x1b[0m:" <<
            std::endl;
      } else {
        std::cerr << VERBOSE_2 << "ABSTRACT SYNTAX TREE:" << std::endl;
      }

      std::string tree = VERBOSE_2 + parser_out.tree->to_string(0, USE_COLOR);

      for (unsigned int i = 0; i < tree.size(); ++i) {
        if (tree[i] == '\n') {
          tree.insert(i + 1, VERBOSE_2);
        }
      }

      std::cerr << tree << std::endl;
    }
  }

  return 0;
}

