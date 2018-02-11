#ifndef _LIBCALC_H
#define _LIBCALC_H

#include <iostream>
#include <vector>

namespace libcalc {

  struct {
    const char OPERATOR { 1 };
    const char SYMBOL   { 2 };
    const char GARBAGE  { 3 };

  } const TOKEN_TYPE;

  struct {
    const char ADD { '+' };
    const char SUB { '-' };
    const char MLT { '*' };
    const char DIV { '/' };
    const char LPN { '(' };
    const char RPN { ')' };
    const char MOD { '%' };
    const char PWR { '^' };
    const char FAC { '!' };

  } const TOKEN_OPERATOR;


  const char TOKEN_SYMBOLS[] {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'e'
  };

  class Token {
    public:
      char type { TOKEN_TYPE.GARBAGE };
      char value { '\0' };
  };

std::vector<Token> parse(const std::string expression);

}

#endif