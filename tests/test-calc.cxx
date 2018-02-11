#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <libcalc.hpp>

#include <iostream>

using namespace std;
using namespace libcalc;

TEST_CASE("Should test is project setup works", "Bootstrap" ) {
  REQUIRE((2 + 2) == 4);
}

TEST_CASE("Should construct a valid Token", "Token") {
  Token *t = new Token();
  REQUIRE(t->type == TOKEN_TYPE.GARBAGE);
  REQUIRE(t->value == '\0');
}

