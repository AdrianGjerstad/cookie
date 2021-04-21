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

#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include "../src/include/util/Filesystem.h"

// Lest Test Framework
#include "../../test/lest.hpp"

const lest::test specification[] = {
  CASE( "fs normalizes paths" ) {
    EXPECT(
        cookie::fs::normalize_path("/foo/bar", "../baz") == "/foo/baz");
  },

  CASE( "fs finds absolute paths" ) {
    EXPECT(
        cookie::fs::absolute_path("foo") == "/home/foo");
  },

  CASE( "fs finds relative paths" ) {
    EXPECT(
        cookie::fs::relative_path("/hello") == "../hello");
  },

  CASE( "fs can split paths up into segments" ) {
    std::deque<std::string> expected = {"foo", "bar", "baz"};
    EXPECT(
        cookie::fs::path_segments("/foo/bar/baz") == expected);
  },

  CASE( "fs gets the proper cwd (current working directory)" ) {
    EXPECT(
        cookie::fs::pwd() == "/home");
  },

  CASE( "fs purges double slashes from file paths" ) {
    EXPECT(
        cookie::fs::remove_doubleslash("/foo//bar//baz/ham") ==
        "/foo/bar/baz/ham");
  }
};

int main(int argc, char** argv) {
  chdir("/home");

  return lest::run(specification, argc, argv);
}

