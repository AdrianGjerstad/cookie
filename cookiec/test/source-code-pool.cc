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

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../src/include/util/SourceCodePool.h"

// Lest Test Framework
#include "../../test/lest.hpp"

const lest::test specification[] = {
  CASE( "SourceCodePool reads files into memory properly" ) {
    cookie::SourceCodePool pool;

    const std::string filename = "cookiec/test/data/code.txt";
    std::ifstream f(filename);
    
    f.seekg(0, f.end);
    unsigned int size = f.tellg();
    char c[size + 1];
    f.seekg(0, f.beg);
    
    f.read(c, size);
    f.close();
    
    c[size] = '\x00';  // Stupid c-style strings
    
    const std::string content = c;

    pool.add(filename);

    const std::string* source = pool.get(filename);
    // DO NOT DEREFERENCE THE STRING IN REAL CODE WITH UNKNOWN SIZES OF DATA!!!!
    EXPECT((*source) == content);
  },

  CASE( "SourceCodePool properly removes files from the pool" ) {
    cookie::SourceCodePool pool;

    // Just an example file that is guaranteed to exist.
    pool.add("/etc/passwd");
    pool.remove("/etc/passwd");

    EXPECT(pool.get("/etc/passwd") == nullptr);
  },

  CASE( "SourceCodePool properly disposes of contents on destruction" ) {
    cookie::SourceCodePool pool;

    pool.add("/etc/passwd");
    pool.add("/etc/group");

    // Emulate destruction of the pool. Destroy/free all source code resources.
    pool.dispose();

    EXPECT(pool.size() == 0u);
  },

  CASE( "SourceCodePool handles missing files correctly" ) {
    cookie::SourceCodePool pool;

    pool.add("/nonexistent");

    EXPECT(pool.get("/nonexistent") == nullptr);
  }
};

int main(int argc, char** argv) {
  return lest::run(specification, argc, argv);
}

