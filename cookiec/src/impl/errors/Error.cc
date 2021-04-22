#include "../../include/errors/Error.h"

#include <string>

#include "../../include/util/Position.h"

namespace cookie {

Error::Error(Position pstart, Position pend, std::string message) :
    pstart_(pstart), pend_(pend), message_(message), name_("error") {
  // Nothing to do
}

Error::Error(
    Position pstart, Position pend, std::string message, std::string name) :
    pstart_(pstart), pend_(pend), message_(message), name_(name) {
  // Nothing to do
}

std::string Error::to_string(bool use_colors) {
  unsigned int line_start = pstart_.index();
  unsigned int line_end = pstart_.index();

  const std::string* source = pstart_.source_code();

  while (
      line_start > 0 &&
      source->at(line_start - 1) != '\n') {
    --line_start;
  }

  while (
      source->size() > line_end &&
      source->at(line_end) != '\n') {
    ++line_end;
  }


  unsigned int line_size = line_end - line_start;

  std::string res;

  if(use_colors) res += "\x1b[1;31m";

  res += pstart_.filename() + ":" + std::to_string(pstart_.line()) +
      ":" + std::to_string(pstart_.col()) + ": " + name_ + ": ";

  if(use_colors) res += "\x1b[0m\x1b[31m";

  res += message_ + "\n  ";

  if(use_colors) res += "\x1b[0m";

  res += pstart_.source_code()->substr(line_start, line_size) + "\n  ";

  if(use_colors) res += "\x1b[34m";

  res += std::string(pstart_.col()-1, ' ') + "^" +
      std::string(pend_.col()-pstart_.col()-1, '~');

  if(use_colors) res += "\x1b[0m";

  return res;
}

}  // namespace cookie

