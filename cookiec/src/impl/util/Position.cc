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

#include "../../include/util/Position.h"

#include "../../include/util/SourceCodePool.h"

namespace cookie {

Position::Position(
    unsigned int line,
    unsigned int col,
    unsigned int index,
    const std::string& filename,
    const std::string* source_code) {
  line_ = line;
  col_ = col;
  index_ = index;
  filename_ = filename;
  source_code_ = source_code;
}

Position::Position(
    unsigned int line,
    unsigned int col,
    unsigned int index,
    const std::string& filename,
    const SourceCodePool& pool) {
  line_ = line;
  col_ = col;
  index_ = index;
  filename_ = filename;
  source_code_ = pool.get(filename);
}

void Position::advance() {
  if (at_end()) return;

  if (character() == '\n') {
    ++line_;
    col_ = 0;
  }

  ++index_;
  ++col_;
}

void Position::advance(unsigned int count) {
  for (unsigned int i = 0; i < count; ++i) advance();
}

void Position::regress() {
  if (at_begin()) return;

  --index_;
  if (character() == '\n') {
    --line_;

    // Find col_
    int i = 1;
    for (; index_-i >= 0 && source_code_->at(i) != '\n'; ++i) {}

    col_ = i + 1;
  }

  --col_;
}

void Position::regress(unsigned int count) {
  for (unsigned int i = 0; i < count; ++i) regress();
}

char Position::character() const {
  return source_code_->at(index_);
}

unsigned int Position::line() const {
  return line_;
}

unsigned int Position::col() const {
  return col_;
}

unsigned int Position::index() const {
  return index_;
}

const std::string& Position::filename() const {
  return filename_;
}

const std::string* Position::source_code() const {
  return source_code_;
}

bool Position::at_end() const {
  return source_code_->size() <= index_;
}

bool Position::at_begin() const {
  return index_ == 0;
}

}  // namespace cookie

