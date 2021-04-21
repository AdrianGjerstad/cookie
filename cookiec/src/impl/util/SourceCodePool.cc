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

#include "../../include/util/SourceCodePool.h"

#include <string>
#include <unordered_map>
#include <fstream>
#include <iterator>
#include <iostream>

#include "../../include/util/Filesystem.h"

namespace cookie {

SourceCodePool::SourceCodePool() {
  // Nothing to do
}

SourceCodePool::~SourceCodePool() {
  dispose();
}

void SourceCodePool::add(std::string filename) {
  filename = cookie::fs::absolute_path(filename);
  std::ifstream f(filename);

  if (!f.is_open()) return;  // The file does not exist

  f.seekg(0, f.end);
  unsigned int length = f.tellg();
  std::string* source = new std::string(length, '\x00');
  f.seekg(0, f.beg);

  unsigned int idx = 0;
  for (std::istreambuf_iterator<char> i(f), e; i != e; ++i, ++idx) {
    source->at(idx) = *i;
  }

  pool_[filename] = source;

  f.close();
}

void SourceCodePool::add_cin(std::string filename) {
  std::string* source = new std::string();

  char c;
  while (std::cin.get(c)) {
    source->push_back(c);
  }

  pool_[filename] = source;
}

void SourceCodePool::add_hardcode(std::string filename, std::string* code) {
  pool_[cookie::fs::absolute_path(filename)] = code;
}

const std::string* SourceCodePool::get(std::string filename) const {
  if (filename == "-") {
    auto it = pool_.find(filename);
    if (it == pool_.end()) return nullptr;
    return (*it).second;
  }

  auto it = pool_.find(cookie::fs::absolute_path(filename));
  if (it == pool_.end()) return nullptr;
  return (*it).second;
}

void SourceCodePool::remove(std::string filename) {
  filename = cookie::fs::absolute_path(filename);
  delete pool_[filename];
  pool_.erase(filename);
}

void SourceCodePool::dispose() {
  for (auto& [ filename, source ] : pool_) {
    delete source;
  }

  pool_.erase(pool_.begin(), pool_.end());
}

unsigned int SourceCodePool::size() const {
  return pool_.size();
}

}  // namespace cookie

