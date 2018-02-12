#include <libcalc.hpp>

namespace libcalc {

/*
 * Token
 */

Token::Token() { }

Token::Token(const char symbol) {
  push(symbol);
}

bool Token::push(const char symbol) {
  char st = symbolType(symbol);

  if (st == TOKEN_TYPE.GARBAGE) {
    return false;
  }

  if (type == TOKEN_TYPE.SYMBOL && st == type) {
    value += symbol;
    return true;
  }

  if (type == TOKEN_TYPE.EMPTY) {
    type = st;
    value = symbol;
    return true;
  }

  if (type == TOKEN_TYPE.OPERATOR &&
      st == TOKEN_TYPE.SYMBOL     &&
      value == "-" ) {
    type = st;
    value += symbol;
    return true;
  }

  return false;
}

/*
 *  Tokenizer
 */

Tokenizer::Tokenizer() { }

Tokenizer::~Tokenizer() {
  clear();
}

Tokenizer::Tokenizer(std::string expression) {
  parse(expression);
}

void Tokenizer::parse(std::string expression) {
  Token *t = new Token();
  tokens.push_back(t);

  for (char e : expression) {
    if (!t->push(e)) {
      t = new Token(e);
      tokens.push_back(t);
    }
  }
}

void Tokenizer::clear() {
  for (Token *t : tokens) {
    delete t;
  }

  tokens.clear();
}

}
