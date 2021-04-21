#ifndef COOKIEC_SRC_INCLUDE_LEXER_TOKEN_H_
#define COOKIEC_SRC_INCLUDE_LEXER_TOKEN_H_

#include <string>

#include "TokenType.h"
#include "../util/Position.h"

namespace cookie {

class Token {
 public:
  Token(Position, Position, TokenType);

  const std::string to_string() const;
  const TokenType type() const;
  const std::string get_value() const;

  // const std::string as_str() const;
  const int32_t as_i32() const;
  const uint32_t as_u32() const;
  const int64_t as_i64() const;
  const uint64_t as_u64() const;
  const float as_f32() const;
  const double as_f64() const;

 private:
  // The value for the token may be extracted via the source data of these
  // Position fields.
  Position pstart_;
  Position pend_;
  TokenType type_;
};

} // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_LEXER_TOKEN_H_

