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

#ifndef COOKIEC_SRC_INCLUDE_UTIL_SOURCECODEPOOL_H_
#define COOKIEC_SRC_INCLUDE_UTIL_SOURCECODEPOOL_H_

#include <string>
#include <unordered_map>

namespace cookie {

class SourceCodePool {
 public:
  SourceCodePool();
  ~SourceCodePool();

  void add(std::string);
  void add_cin(std::string);
  const std::string* get(std::string) const;
  void remove(std::string);

  // void cookie::SourceCodePool::dispose()
  //
  // Delete all source code from the pool. This is typically done during the
  // destructor of this class.
  void dispose();

  unsigned int size() const;
 private:
  std::unordered_map<std::string, std::string*> pool_;
};

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_UTIL_SOURCECODEPOOL_H_

