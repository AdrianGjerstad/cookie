#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <igloo/igloo_alt.h>
using namespace igloo;

#include "../src/include/util/SourceCodePool.h"

Describe(source_code_pool) {
  void SetUp() {
    
  }

  It(reads_files_correctly) {
    cookie::SourceCodePool pool;
    
    const std::string filename = "cookiec/test/data/code.txt";
    std::ifstream f(filename);
    f.seekg(0, f.end);
    unsigned int size = f.tellg();
    char c[size+1];
    f.seekg(0, f.beg);
    f.read(c, size);
    f.close();
    c[size] = '\x00';  // Stupid c-style strings
    const std::string content = c;

    pool.add(filename);
    
    const std::string* source = pool.get(filename);
    // DO NOT DEREFERENCE THE STRING IN REAL CODE WITH UNKNOWN SIZES OF DATA!!!!
    Assert::That(*source, Equals(content));
  }

  It(deletes_files_correctly) {
    cookie::SourceCodePool pool;
    
    pool.add("/etc/passwd");  // Just an example file that is guaranteed to exist.
    pool.remove("/etc/passwd");

    Assert::That(pool.get("/etc/passwd"), Equals(nullptr));
  }

  It(disposes_files_correctly) {
    cookie::SourceCodePool pool;
    
    pool.add("/etc/passwd");
    pool.add("/etc/group");
    
    // Emulate destruction of the pool. Destroy/free all source code resources.
    pool.dispose();

    Assert::That(pool.size(), Equals(0));
  }

  It(handles_missing_files_correctly) {
    cookie::SourceCodePool pool;

    pool.add("/nonexistent");

    Assert::That(pool.get("/nonexistent"), Equals(nullptr));
  }
};

int main(int argc, char** argv) {
  return TestRunner::RunAllTests(argc, argv);
}

