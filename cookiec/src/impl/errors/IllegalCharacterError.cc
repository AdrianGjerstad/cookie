#include "../../include/errors/IllegalCharacterError.h"

#include "../../include/errors/Error.h"
#include "../../include/util/Position.h"

namespace cookie {

IllegalCharacterError::IllegalCharacterError(
    Position pstart, Position pend, std::string message) :
    Error(pstart, pend, message, "illegal-character-error") {
  // Nothing to do
}

}  // namespace cookie

