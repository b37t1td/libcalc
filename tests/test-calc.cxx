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
  REQUIRE(t->type == TOKEN_TYPE.EMPTY);
  delete t;

  t = new Token('3');
  REQUIRE(t->type == TOKEN_TYPE.SYMBOL);
  delete t;

  t = new Token('+');
  REQUIRE(t->type == TOKEN_TYPE.OPERATOR);
  delete t;
}

TEST_CASE("Should parse basic expressions for Tokenizer", "Tokenizer") {
  std::string expr = "22 + 44";

  Tokenizer *t = new Tokenizer(expr);
  REQUIRE(t->tokens[0]->value == "22");
  REQUIRE(t->tokens[0]->type == TOKEN_TYPE.SYMBOL);
  REQUIRE(t->tokens[1]->value == "+");
  REQUIRE(t->tokens[1]->type == TOKEN_TYPE.OPERATOR);
  REQUIRE(t->tokens.size() == 3);
  REQUIRE(t->tokens[2]->value == "44");

  delete t;
}

TEST_CASE("Should parse negative values", "Tokenizer") {
  std::string expr = "-22 * -44 + 2 * -3";

  Tokenizer *t = new Tokenizer(expr);

  REQUIRE(t->tokens[0]->value == "-22");
  REQUIRE(t->tokens[2]->value == "-44");
  REQUIRE(t->tokens[4]->value == "2");
  REQUIRE(t->tokens[6]->value == "-3");

  delete t;
}

TEST_CASE("Should parse non-regular numbers", "Tokenizer") {
  std::string expr = "-2.2 * -4e5.14158 + 2 * -3.02";

  Tokenizer *t = new Tokenizer(expr);

  REQUIRE(t->tokens[0]->value == "-2.2");
  REQUIRE(t->tokens[2]->value == "-4e5.14158");

  delete t;
}

