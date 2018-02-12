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

const char TOKEN_SYMBOLS[] = "0123456789+-*/()%^!e.";
const short TOKEN_SYMBOLS_LEN = sizeof(TOKEN_SYMBOLS);

const char symbolType(const char symbol);
bool isOperator(const char symbol);

class Token {
  public:
    Token();
    Token(const char symbol);
    char type;
    char value;

  private:
    void create(const char symbol);
};

class Tokenizer {
  public:
    Tokenizer(std::string expression);
    Tokenizer();
    ~Tokenizer();
    void parse(std::string expression);

  private:
    std::vector<Token *> tokens;
    void clear();
};

}

#endif