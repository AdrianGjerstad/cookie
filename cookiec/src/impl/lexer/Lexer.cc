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

#include "../../include/lexer/Lexer.h"

#include <vector>
#include <string>
#include <algorithm>

#include "../../include/lexer/Token.h"
#include "../../include/lexer/TokenType.h"
#include "../../include/util/Position.h"
#include "../../include/util/SourceCodePool.h"
#include "../../include/structs/LexerResult.h"
#include "../../include/errors/IllegalCharacterError.h"
#include "../../include/errors/CommentError.h"

namespace cookie {

Lexer::Lexer(const SourceCodePool* pool) : pool_(pool) {
  // Nothing to do
}

LexerResult Lexer::lex(const std::string& filename) const {
  Position pos(1, 1, 0, filename, pool_->get(filename));
  LexerResult result;

  const std::string DIGITS = "0123456789";
  const std::string START_IDENT =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$";
  const std::string IGNORE = " \t\n\r";

  bool single_line_comment = false;
  unsigned int block_comment = 0;
  while (!pos.at_end()) {
    char ch = pos.character();

    // Single line comments
    if (single_line_comment && ch == '\n') {
      single_line_comment = false;
      pos.advance();
      continue;
    } else if (single_line_comment) {
      pos.advance();
      continue;
    }

    // Block comments
    if (ch == '/') {
      if (pos.source_code()->at(pos.index()+1) == '*') {
        ++block_comment;
        pos.advance();
        pos.advance();
      }
    } else if (block_comment != 0 && ch == '*') {
      if (pos.source_code()->at(pos.index()+1) == '/') {
        --block_comment;
        pos.advance();
        pos.advance();
        ch = pos.character();
      }
    }

    if (block_comment) {
      pos.advance();
      continue;
    }

    if (IGNORE.find(ch) != std::string::npos) {
      pos.advance();
    } else if (DIGITS.find(ch) != std::string::npos) {
      result.tokens.push_back(make_number_(&pos));
    } else if (START_IDENT.find(ch) != std::string::npos) {
      result.tokens.push_back(make_identifier_(&pos));
    } else if (ch == '+') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::PLUS));
    } else if (ch == '-') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::MINUS));
    } else if (ch == '*') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::STAR));
    } else if (ch == '/') {
      Position pstart(pos);
      pos.advance();
      if (pos.character() == '/') {
        single_line_comment = true;
        pos.advance();
        continue;
      }

      result.tokens.push_back(Token(pstart, pos, TokenType::SLASH));
    } else if (ch == '%') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::PERCENT));
    } else if (ch == '&') {
      Position pstart(pos);
      pos.advance();

      if (pos.character() == '&') {
        pos.advance();
        result.tokens.push_back(Token(pstart, pos, TokenType::DOUBLE_AMPERSAND)
            );
      } else {
        result.tokens.push_back(Token(pstart, pos, TokenType::AMPERSAND));
      }
    } else if (ch == '|') {
      Position pstart(pos);
      pos.advance();

      if (pos.character() == '|') {
        pos.advance();
        result.tokens.push_back(Token(pstart, pos, TokenType::DOUBLE_PIPE));
      } else {
        result.tokens.push_back(Token(pstart, pos, TokenType::PIPE));
      }
    } else if (ch == '^') {
      Position pstart(pos);
      pos.advance();

      if (pos.character() == '^') {
        pos.advance();
        result.tokens.push_back(Token(pstart, pos, TokenType::DOUBLE_CARET));
      } else {
        result.tokens.push_back(Token(pstart, pos, TokenType::CARET));
      }
    } else if (ch == '>') {
      result.tokens.push_back(make_gt_(&pos));
    } else if (ch == '<') {
      result.tokens.push_back(make_lt_(&pos));
    } else if (ch == '~') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::TILDE));
    } else if (ch == '(') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::LEFT_PARENTHESIS));
    } else if (ch == ')') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::RIGHT_PARENTHESIS));
    } else if (ch == '{') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::LEFT_BRACE));
    } else if (ch == '}') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::RIGHT_BRACE));
    } else if (ch == '[') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::LEFT_BRACKET));
    } else if (ch == ']') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::RIGHT_BRACKET));
    } else if (ch == '=') {
      result.tokens.push_back(make_equals_(&pos));
    } else if (ch == '!') {
      Position pstart(pos);
      pos.advance();

      if (pos.character() == '=') {
        pos.advance();
        result.tokens.push_back(Token(pstart, pos, TokenType::BANG_EQUALS));
      } else {
        result.tokens.push_back(Token(pstart, pos, TokenType::BANG));
      }
    } else if (ch == ';') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::SEMICOLON));
    } else if (ch == ',') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::COMMA));
    } else {
      Position pstart(pos);
      pos.advance();

      result.errors.push_back(IllegalCharacterError(
        pstart, pos, std::string("unlexable character: '") + ch + "'"
      ));
    }
  }

  if (block_comment) {
    pos.regress();
    Position pstart(pos);
    pos.advance();
    result.errors.push_back(CommentError(
      pstart, pos,
      std::string("still waiting for ") + std::to_string(block_comment) +
      " level" + (block_comment==1?"":"s") + " of block comments to close"));
  }

  result.tokens.push_back(Token(pos, pos, TokenType::END_OF_FILE));

  return result;
}

Token Lexer::make_number_(Position* pos) const {
  const std::string DIGITS = "0123456789";
  Position pstart(*pos);
  pos->advance();

  bool dot = false;
  bool is_unsigned = false;
  bool is_64bit = false;

  while (
      DIGITS.find(pos->character()) != std::string::npos ||
      pos->character() == '.') {
    if (pos->character() == '.') {
      if (dot) {
        break;
      } else {
        dot = true;
        is_64bit = true;
      }
    }

    pos->advance();
  }

  Position pend(*pos);
  pos->regress();
  if (pos->character() == '.') {
    pend = *pos;
  }
  pos->advance();

  if (!dot) {
    // This will be an integral type.
    do {
      if (pos->character() == 'f') {
        dot = true;
        is_64bit = false;
        pos->advance();
        break;
      }

      if (pos->character() == 'u') {
        is_unsigned = true;
        pos->advance();
      }

      if (pos->character() == 'l') {
        is_64bit = true;
        pos->advance();
      }
    } while (false);
  } else {
    // This will be a floating-point type.
    if (pos->character() == 'f') {
      is_64bit = false;
      pos->advance();
    }
  }

  if (dot) {
    if (is_64bit) {
      return Token(pstart, pend, TokenType::FLOAT64);
    }

    return Token(pstart, pend, TokenType::FLOAT32);
  }

  if (is_unsigned) {
    if (is_64bit) {
      return Token(pstart, pend, TokenType::UINT64);
    }

    return Token(pstart, pend, TokenType::UINT32);
  } else {
    if (is_64bit) {
      return Token(pstart, pend, TokenType::INT64);
    }

    return Token(pstart, pend, TokenType::INT32);
  }
}

Token Lexer::make_identifier_(Position* pos) const {
  std::string tmp;

  Position pstart(*pos);
  tmp += pos->character();
  pos->advance();

  std::string CONT =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$0123456789";

  while (CONT.find(pos->character()) != std::string::npos) {
    tmp += pos->character();
    pos->advance();
  }

  Position pend(*pos);

  std::vector<std::string> kw_type_s = {
    "i32", "u32", "i64", "u64", "f32", "f64", "bool"
  };

  if (std::find(kw_type_s.begin(), kw_type_s.end(), tmp) !=
      kw_type_s.end()) {
    return Token(pstart, pend, TokenType::KW_DATA_TYPE);
  } else if (tmp == "true" || tmp == "false") {
    return Token(pstart, pend, TokenType::BOOLEAN);
  } else if (tmp == "void") {
    return Token(pstart, pend, TokenType::KW_VOID);
  } else if (tmp == "return") {
    return Token(pstart, pend, TokenType::KW_RETURN);
  } else if (tmp == "const") {
    return Token(pstart, pend, TokenType::KW_CONST);
  } else if (tmp == "export") {
    return Token(pstart, pend, TokenType::KW_EXPORT);
  } else if (tmp == "if") {
    return Token(pstart, pend, TokenType::KW_IF);
  } else if (tmp == "else") {
    return Token(pstart, pend, TokenType::KW_ELSE);
  }

  return Token(pstart, pend, TokenType::IDENTIFIER);
}

Token Lexer::make_lt_(Position* pos) const {
  Position pstart(*pos);
  pos->advance();

  if (pos->character() == '<') {
    pos->advance();
    return Token(pstart, *pos, TokenType::DOUBLE_LESS);
  } else if (pos->character() == '=') {
    pos->advance();
    return Token(pstart, *pos, TokenType::LESS_EQUALS);
  } else {
    return Token(pstart, *pos, TokenType::LESS);
  }
}

Token Lexer::make_gt_(Position* pos) const {
  Position pstart(*pos);
  pos->advance();

  if (pos->character() == '>') {
    pos->advance();
    return Token(pstart, *pos, TokenType::DOUBLE_GREATER);
  } else if (pos->character() == '=') {
    pos->advance();
    return Token(pstart, *pos, TokenType::GREATER_EQUALS);
  } else {
    return Token(pstart, *pos, TokenType::GREATER);
  }
}

Token Lexer::make_equals_(Position* pos) const {
  Position pstart(*pos);
  pos->advance();

  if (pos->character() == '=') {
    pos->advance();
    return Token(pstart, *pos, TokenType::DOUBLE_EQUALS);
  } else {
    return Token(pstart, *pos, TokenType::EQUALS);
  }
}

}  // namespace cookie

