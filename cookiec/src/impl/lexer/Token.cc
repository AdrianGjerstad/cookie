#include "../../include/lexer/Token.h"

#include <string>

#include "../../include/lexer/TokenType.h"
#include "../../include/util/Position.h"

namespace cookie {

Token::Token(Position pstart, Position pend, TokenType type) :
    pstart_(pstart), pend_(pend), type_(type) {
  // Nothing to do.
}

const std::string Token::to_string() const {
  return
      std::string("cookie::Token<") + type_.to_string() +
      ">(\"" + get_value() + "\")";
}

const TokenType Token::type() const {
  return type_;
}

const std::string Token::get_value() const {
  // Don't call this method constantly. For optimization purposes, Token does
  // not store the raw value itself.
  std::string res(pend_.index() - pstart_.index(), '\x00');

  const unsigned int start_index = pstart_.index();
  for(unsigned int i = start_index; i < pend_.index(); ++i) {
    res[i-start_index] = pstart_.source_code()->at(i);
  }

  return res;
}

const int32_t Token::as_i32() const {
  return std::stoi(get_value());
}

const uint32_t Token::as_u32() const {
  return std::stoul(get_value());
}

const int64_t Token::as_i64() const {
  return std::stol(get_value());
}

const uint64_t Token::as_u64() const {
  return std::stoul(get_value());
}

const float Token::as_f32() const {
  return std::stof(get_value());
}

const double Token::as_f64() const {
  return std::stod(get_value());
}

}  // namespace cookie

