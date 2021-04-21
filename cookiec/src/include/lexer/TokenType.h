#ifndef COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_
#define COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_

#include <string>

namespace cookie {

class TokenType {
 public:
  TokenType(std::string);

  const std::string to_string() const;

  static const TokenType INT32;    // signed i32 literal
  static const TokenType UINT32;   // unsigned i32 literal
  static const TokenType INT64;    // signed i64 literal
  static const TokenType UINT64;   // unsigned i64 literal
  static const TokenType FLOAT32;  // float literal
  static const TokenType FLOAT64;  // double literal
  
  static const TokenType PLUS;     // +
  static const TokenType MINUS;    // -
  static const TokenType STAR;     // *
  static const TokenType SLASH;    // /
  static const TokenType PERCENT;  // %
  
  static const TokenType LEFT_PARENTHESIS;   // (
  static const TokenType RIGHT_PARENTHESIS;  // )
 private:
  std::string repr_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_TOKENTYPE_H_

