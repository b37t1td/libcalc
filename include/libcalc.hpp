#ifndef _LIBCALC_H
#define _LIBCALC_H

#include <iostream>
#include <vector>

namespace libcalc {

struct {
  const char EMPTY    { 0 };
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

const char TOKEN_SYMBOLS[] = "0123456789+-*/()%^!e.";
const short TOKEN_SYMBOLS_LEN = sizeof(TOKEN_SYMBOLS);

const char symbolType(const char symbol);
bool isOperator(const char symbol);

class Token {
  public:
    std::string value;
    char type { TOKEN_TYPE.EMPTY };

    Token();
    Token(const char symbol);
    bool push(const char symbol);
};

class Tokenizer {
  public:
    std::vector<Token *> tokens;

    Tokenizer();
    ~Tokenizer();
    Tokenizer(std::string expression);
    void parse(std::string expression);
    double evaluate();
    std::vector<Token *> toRPN();

  private:
    void clear();
};

std::string t2s(std::vector<Token *> tokens);
int factorial(int n);

double eval(std::string expr);
}

#endif