#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <libcalc.hpp>

TEST_CASE("Should test is project setup works", "Bootstrap" ) {
  REQUIRE((2 + 2) == 4);
}


