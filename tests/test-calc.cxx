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

TEST_CASE("Should generate a valid RPN", "Tokenizer") {
  std::string expr1 = "-4 * ( 2 + -2) - 1";
  std::string expr2 = "4 * ( 2 + 2) - 1";
  std::string expr3 = "( 2 - 3 ) * 2 + 4 / 2";
  std::string expr4 = "( 2 - 3 ) % 2 + 4 ^ 2 + 2";
  std::string expr5 = "( 2 - 3 ) % 2 + 4 ! 2 + 2";

  Tokenizer *t = new Tokenizer(expr1);
  REQUIRE(t2s(t->toRPN()) == "-4 2 -2 + * 1 -");
  delete t;

  t = new Tokenizer(expr2);
  REQUIRE(t2s(t->toRPN()) == "4 2 2 + * 1 -");
  delete t;

  t = new Tokenizer(expr3);
  REQUIRE(t2s(t->toRPN()) == "2 3 - 2 * 4 2 / +");
  delete t;

  t = new Tokenizer(expr4);
  REQUIRE(t2s(t->toRPN()) == "2 3 - 2 % 4 2 ^ + 2 +");
  delete t;

  t = new Tokenizer(expr5);
  REQUIRE(t2s(t->toRPN()) == "2 3 - 2 % 4 2 ! + 2 +");
  delete t;
}

TEST_CASE("Should evaluate RPN", "Tokenizer") {
  std::string expr = "( 5 - 3 ) * 2";

  Tokenizer *t = new Tokenizer(expr);
  REQUIRE(t->evaluate() == 4);
  delete t;

  expr = "2 + 4 * 2";

  t = new Tokenizer(expr);
  REQUIRE(t->evaluate() == 10);
  delete t;

  expr = "1 + (3 % 3)";

  t = new Tokenizer(expr);
  REQUIRE(t->evaluate() == 1);
  delete t;
}

TEST_CASE("Should provide very basic API", "libcalc") {
  REQUIRE(eval("2 + 2") == 4);
  REQUIRE(eval("2 * ( 1 + 1 )") == 4);
  REQUIRE(eval("( 1 + 1 ) * 2") == 4);
  REQUIRE(eval("(5 - 4) + 3") == 4);
  REQUIRE(eval("6 / ( 1 + 2) + 2") == 4);
}

