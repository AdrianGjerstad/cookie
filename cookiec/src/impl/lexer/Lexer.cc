#include "../../include/lexer/Lexer.h"

#include <vector>
#include <string>
#include <iostream>

#include "../../include/lexer/Token.h"
#include "../../include/lexer/TokenType.h"
#include "../../include/util/Position.h"
#include "../../include/util/SourceCodePool.h"
#include "../../include/structs/LexerResult.h"
#include "../../include/errors/IllegalCharacterError.h"

namespace cookie {

Lexer::Lexer(const SourceCodePool* pool) : pool_(pool) {
  // Nothing to do
}

LexerResult Lexer::lex(const std::string& filename) const {
  Position pos(1, 1, 0, filename, pool_->get(filename));
  LexerResult result;

  const std::string DIGITS = "0123456789";
  const std::string IGNORE = " \t\n\r";

  while (!pos.at_end()) {
    char ch = pos.character();

    if (IGNORE.find(ch) != std::string::npos) {
      pos.advance();
    } else if (DIGITS.find(ch) != std::string::npos) {
      result.tokens.push_back(make_number_(&pos));
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
      result.tokens.push_back(Token(pstart, pos, TokenType::SLASH));
    } else if (ch == '%') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::PERCENT));
    } else if (ch == '(') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::LEFT_PARENTHESIS));
    } else if (ch == ')') {
      Position pstart(pos);
      pos.advance();
      result.tokens.push_back(Token(pstart, pos, TokenType::RIGHT_PARENTHESIS));
    } else {
      Position pstart(pos);
      pos.advance();

      result.errors.push_back(IllegalCharacterError(
        pstart, pos, std::string("unlexable character: '") + ch + "'"
      ));
    }
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
  if(pos->character() == '.') {
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
    } while(false);
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

}  // namespace cookie

