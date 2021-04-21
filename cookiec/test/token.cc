#include <iostream>
#include <string>
#include <random>

#include "../src/include/lexer/Token.h"
#include "../src/include/lexer/TokenType.h"
#include "../src/include/util/Position.h"
#include "../src/include/util/SourceCodePool.h"

#include "../../test/lest.hpp"

#define ITERATIONS           1023

const lest::test specification[] = {
  CASE( "Token retrieves strings properly" ) {
    cookie::SourceCodePool pool;

    pool.add("cookiec/test/data/example.cookie");
    const std::string* source = pool.get("cookiec/test/data/example.cookie");

    const std::string expected = source->substr(12, 10);
    cookie::Position pstart(1, 1, 0, "cookiec/test/data/example.cookie", source);
    for(int i = 0; i < 12; ++i) pstart.advance();
    
    cookie::Position pend(1, 1, 0, "cookiec/test/data/example.cookie", source);
    for(int i = 0; i < 22; ++i) pend.advance();
    
    cookie::Token token(pstart, pend, cookie::TokenType::INT32);

    EXPECT(token.get_value() == expected);
  },
  
  CASE( "Token retrieves numbers (i32) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-65536, 65535);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const int expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::INT32);
  
      EXPECT(token.as_i32() == expected);
  
      pool.remove("code");
    }
  },
  
  CASE( "Token retrieves numbers (u32) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned int> distribution(0, 65535);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const unsigned int expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::UINT32);
  
      EXPECT(token.as_u32() == expected);
  
      pool.remove("code");
    }
  },

  CASE( "Token retrieves numbers (i64) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution(-655360000, 655350000);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const long expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::INT64);
  
      EXPECT(token.as_i64() == expected);
  
      pool.remove("code");
    }
  },
  
  CASE( "Token retrieves numbers (u64) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned long> distribution(0, 655350000);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const unsigned long expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::UINT64);
  
      EXPECT(token.as_u64() == expected);
  
      pool.remove("code");
    }
  },
  
  CASE( "Token retrieves numbers (f32) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-65536.f, 65535.f);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const float expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::FLOAT32);
   
      // Stupid hack to get rid of floating point precision los
      EXPECT(std::to_string(token.as_f32()) == std::to_string(expected));
  
      pool.remove("code");
    }
  },

  CASE( "Token retrieves numbers (f64) properly" ) {
    cookie::SourceCodePool pool;
  
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-65536., 65535.);
    
    for(unsigned int test_i = 0; test_i < ITERATIONS; ++test_i) {
      const double expected = distribution(generator);
      std::string* source = new std::string(std::to_string(expected));
      pool.add_hardcode("code", source);
  
      cookie::Position pstart(1, 1, 0, "code", source);
      cookie::Position pend(1, source->size()+1, source->size(), "code", source);
      cookie::Token token(pstart, pend, cookie::TokenType::FLOAT64);
      
      // Stupid hack to get rid of floating point precision loss
      EXPECT(std::to_string(token.as_f64()) == std::to_string(expected));
  
      pool.remove("code");
    }
  }
};

int main(int argc, char** argv) {
  return lest::run(specification, argc, argv);
}

