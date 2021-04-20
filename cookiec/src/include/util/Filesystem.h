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

#ifndef COOKIEC_SRC_INCLUDE_UTIL_FILESYSTEM_H_
#define COOKIEC_SRC_INCLUDE_UTIL_FILESYSTEM_H_

#include <string>
#include <vector>
#include <deque>

namespace cookie {

namespace fs {

std::string pwd();
std::deque<std::string> path_segments(std::string);
std::string shortest_path_representation(std::string);
std::string relative_path(std::string);
std::string absolute_path(std::string);
std::string normalize_path(std::string, std::string);
std::string remove_doubleslash(std::string);

}  // namespace fs

}  // namespace cookie

#endif  // COOKIEC_SRC_INCLUDE_UTIL_FILESYSTEM_H_

