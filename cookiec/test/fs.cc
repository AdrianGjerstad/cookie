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
#include <igloo/igloo_alt.h>

Describe(filesystem) {
  Describe(paths) {
    It(normalizes_paths) {
      igloo::Assert::That(
          cookie::fs::normalize_path("/foo/bar", "../baz"),
          igloo::Equals("/foo/baz"));
    }

    It(forces_absolute_paths) {
      igloo::Assert::That(
          cookie::fs::absolute_path("foo"),
          igloo::Equals("/home/foo"));
    }

    It(forces_relative_paths) {
      igloo::Assert::That(
          cookie::fs::relative_path("/hello"),
          igloo::Equals("../hello"));
    }

    It(produces_path_segments) {
      igloo::Assert::That(
          cookie::fs::path_segments("/foo/bar/baz"),
          igloo::Equals<std::deque<std::string>>({"foo", "bar", "baz"}));
    }

    It(produces_pwd) {
      igloo::Assert::That(
          cookie::fs::pwd(),
          igloo::Equals("/home"));
    }

    It(purges_double_slashes) {
      igloo::Assert::That(
          cookie::fs::remove_doubleslash("/foo//bar//baz/ham"),
          igloo::Equals("/foo/bar/baz/ham"));
    }
  };
};

int main(int argc, char** argv) {
  chdir("/home");

  return igloo::TestRunner::RunAllTests(argc, argv);
}

