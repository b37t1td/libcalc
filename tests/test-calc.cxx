#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <libcalc.hpp>

#include <iostream>

using namespace std;
using namespace libcalc;

TEST_CASE("Should test is project setup works", "Bootstrap" ) {
  REQUIRE((2 + 2) == 4);
}

TEST_CASE("Should construct a valid Token", "Tokenizer") {
  Token *t = new Token();
  REQUIRE(t->type == TOKEN_TYPE.GARBAGE);
  delete t;

  t = new Token('3');
  REQUIRE(t->value == '3');
  REQUIRE(t->type == TOKEN_TYPE.SYMBOL);

  delete t;

  t = new Token('+');
  REQUIRE(t->value == '+');
  REQUIRE(t->type == TOKEN_TYPE.OPERATOR);
}


TEST_CASE("Should parse basic expressions for Tokenizer", "Tokenizer") {
  std::string expr = "22 + 44";

  Tokenizer *t = new Tokenizer(expr);
  delete t;

  t = new Tokenizer(expr);

}

