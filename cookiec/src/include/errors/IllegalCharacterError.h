#ifndef COOKIEC_SRC_INCLUDE_ERRORS_ILLEGALCHARACTERERROR_H_
#define COOKIEC_SRC_INCLUDE_ERRORS_ILLEGALCHARACTERERROR_H_

#include <string>

#include "Error.h"
#include "../util/Position.h"

namespace cookie {

class IllegalCharacterError: public Error {
 public:
  IllegalCharacterError(Position, Position, std::string);
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_ERRORS_ILLEGALCHARACTERERROR_H_

