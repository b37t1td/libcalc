#include <libcalc.hpp>

namespace libcalc {

const char symbolType(const char symbol) {
  bool isValid = false;

  for (short i = 0; i < TOKEN_SYMBOLS_LEN; i++) {
    if (TOKEN_SYMBOLS[i] == symbol) {
      isValid = true;
      break;
    }
  }

  if (isValid == false) {
    return TOKEN_TYPE.GARBAGE;
  }

  return isOperator(symbol) ? TOKEN_TYPE.OPERATOR : TOKEN_TYPE.SYMBOL;
}

bool isOperator(const char symbol) {
  return (
      symbol == TOKEN_OPERATOR.ADD ||
      symbol == TOKEN_OPERATOR.SUB ||
      symbol == TOKEN_OPERATOR.MLT ||
      symbol == TOKEN_OPERATOR.DIV ||
      symbol == TOKEN_OPERATOR.LPN ||
      symbol == TOKEN_OPERATOR.RPN ||
      symbol == TOKEN_OPERATOR.MOD ||
      symbol == TOKEN_OPERATOR.PWR ||
      symbol == TOKEN_OPERATOR.FAC
      );
}

Token::Token() {
  create(-1);
}

Token::Token(const char symbol) {
  create(symbol);
}

void Token::create(const char symbol) {
  type = symbolType(symbol);
  value = symbol;
}

}
