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

std::string t2s(std::vector<Token *> tokens) {
  std::string out;

  for (Token *t : tokens) {
    out += t->value + " ";
  }

  out.erase(out.length() - 1);

  return out;
}

int factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double eval(std::string expr) {
  double result = 0;

  Tokenizer *t = new Tokenizer(expr);
  result = t->evaluate();
  delete t;

  return result;
}

}