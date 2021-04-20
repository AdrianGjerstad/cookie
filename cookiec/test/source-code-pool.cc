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
    
    const std::string content = "Hello, world!\nHello, world!\n";
    const std::string filename = "/tmp/cookiec--source-code-pool.txt";
    std::ofstream f(filename);
    
    f.write(content.c_str(), content.size());
    f.close();

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

