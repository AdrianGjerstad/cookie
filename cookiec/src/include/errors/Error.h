#ifndef COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_
#define COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_

#include <string>

#include "../util/Position.h"

namespace cookie {

class Error {
 public:
  Error(Position, Position, std::string);

  std::string to_string(bool);

 protected:
  Position pstart_;
  Position pend_;
  std::string message_;
  std::string name_;

  Error(Position, Position, std::string, std::string);
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_ERRORS_ERROR_H_

