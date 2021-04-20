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

#include "../../include/util/Filesystem.h"

#include <unistd.h>
#include <limits.h>

#include <string>
#include <vector>
#include <deque>

namespace cookie {

namespace fs {

std::string pwd() {
  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);
  return cwd;
}

std::deque<std::string> path_segments(std::string a) {
  std::deque<std::string> segments;
  std::string segment;
  for (unsigned int i = 0; i < a.size(); ++i) {
    if (a[i] == '/') {
      if (segment.size()) segments.push_back(segment);
      segment = "";
    } else {
      segment += a[i];
    }
  }

  if (segment.size()) segments.push_back(segment);

  return segments;
}

std::string shortest_path_representation(std::string a) {
  std::string absolute = absolute_path(a);
  std::string relative = relative_path(a);

  if (absolute.size() > relative.size()) return relative;
  return absolute;
}

std::string relative_path(std::string a) {
  if (a.size() && a[0] != '/') {
    return a;  // Already a relative path
  }

  // Path is absolute
  std::string cwd = pwd();
  std::deque<std::string> segments = path_segments(a);
  std::deque<std::string> pwd_segments = path_segments(cwd);

  for (unsigned int i = 0; i < pwd_segments.size(); ++i) {
    segments.push_front("..");
  }

  try {
    while (
        pwd_segments.size() &&
        pwd_segments[0] == segments[pwd_segments.size()]) {
      segments.erase(
          segments.begin()+(pwd_segments.size()-1),
          segments.begin()+(pwd_segments.size()+1));
      pwd_segments.pop_front();
    }
  } catch (...) {}

  std::string res;

  for (unsigned int i = 0; i < segments.size(); ++i) {
    res += segments[i];
    if (i+1 != segments.size()) res += '/';
  }

  return res;
}

std::string absolute_path(std::string a) {
  return normalize_path(a, "");
}

std::string normalize_path(std::string a, std::string b) {
  std::string cwd = pwd();

  if (a.size() && a[0] != '/') {
    a = cwd + '/' + a;
  }

  std::deque<std::string> a_segments = path_segments(a);
  std::deque<std::string> b_segments = path_segments(b);

  std::deque<std::string> segments;
  for (unsigned int i = 0; i < a_segments.size(); ++i) {
    if (a_segments[i] == "..") {
      segments.pop_back();
    } else if (a_segments[i] != ".") {
      segments.push_back(a_segments[i]);
    }
  }

  for (unsigned int i = 0; i < b_segments.size(); ++i) {
    if (b_segments[i] == "..") {
      segments.pop_back();
    } else if (b_segments[i] != ".") {
      segments.push_back(b_segments[i]);
    }
  }

  std::string res;
  for (unsigned int i = 0; i < segments.size(); ++i) {
    res += '/';
    res += segments[i];
  }

  return res;
}

std::string remove_doubleslash(std::string a) {
  std::deque<std::string> segments = path_segments(a);

  std::string res = (a.size() && a[0] == '/' ? "/" : "");
  for (unsigned int i = 0; i < segments.size(); ++i) {
    res += segments[i];
    if (i+1 != segments.size()) res += '/';
  }

  return res;
}

}  // namespace fs

}  // namespace cookie

