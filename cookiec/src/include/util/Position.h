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

#ifndef COOKIEC_SRC_INCLUDE_UTIL_POSITION_H_
#define COOKIEC_SRC_INCLUDE_UTIL_POSITION_H_

#include <string>

#include "SourceCodePool.h"

namespace cookie {

class Position {
 public:
  // Initialization constructor
  //
  // - line: Line number to start iterating on; commonly set to 1
  // - col: Column number to start iterating on; commonly set to 1
  // - index: Position, in bytes, to start iterating over source code; commonly
  //   set to 0
  // - filename: Filename of source code. (no intrinsic value except for debug)
  // - source: A pointer to heap-allocated source code.
  //
  // EXAMPLE:
  // Position(1, 1, 0, "/foo/bar", pool.get("/foo/bar"));
  Position(unsigned int,
           unsigned int,
           unsigned int,
           const std::string&,
           const std::string*);
  // OR
  // Position(1, 1, 0, "/foo/bar", pool);
  Position(unsigned int,
           unsigned int,
           unsigned int,
           const std::string&,
           const SourceCodePool&);

  // Advance the reading "head" by one byte.
  //
  // When a newline is encountered, line() increments after the newline has been
  // passed.
  void advance();
  void advance(unsigned int);

  // Regress/deadvance the reading "head" by one byte.
  //
  // When a newline is encountered, line() decrements immediately. THIS METHOD
  // MAY INCUR ADDITIONAL PROCESSING, ESPECIALLY FOR LONG LINES OF CODE, AS
  // POSITION MUST FIND THE NUMBER FOR COLUMN.
  void regress();
  void regress(unsigned int);

  // Get the character under the reading "head"
  char character() const;

  // Getters for obvious attributes of Position
  unsigned int line() const;
  unsigned int col() const;
  unsigned int index() const;
  const std::string& filename() const;
  const std::string* source_code() const;

  // Is the read head at the end or beginning of the source file?
  bool at_end() const;
  bool at_begin() const;

 private:
  unsigned int line_;
  unsigned int col_;
  unsigned int index_;
  std::string filename_;
  const std::string* source_code_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_UTIL_POSITION_H_

