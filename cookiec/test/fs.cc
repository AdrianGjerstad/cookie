#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unistd.h>

#include "../src/include/util/Filesystem.h"

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe(filesystem) {
  Describe(paths) {
    It(normalizes_paths) {
      Assert::That(cookie::fs::normalize_path("/foo/bar", "../baz"), Equals("/foo/baz"));
    }

    It(forces_absolute_paths) {
      Assert::That(cookie::fs::absolute_path("foo"), Equals("/home/foo"));
    }

    It(forces_relative_paths) {
      Assert::That(cookie::fs::relative_path("/hello"), Equals("../hello"));
    }

    It(produces_path_segments) {
      Assert::That(cookie::fs::path_segments("/foo/bar/baz"), Equals<std::deque<std::string>>({"foo", "bar", "baz"}));
    }

    It(produces_pwd) {
      Assert::That(cookie::fs::pwd(), Equals("/home"));
    }

    It(purges_double_slashes) {
      Assert::That(cookie::fs::remove_doubleslash("/foo//bar//baz/ham"), Equals("/foo/bar/baz/ham"));
    }
  };
};

int main(int argc, char** argv) {
  chdir("/home");

  return TestRunner::RunAllTests(argc, argv);
}

