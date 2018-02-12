#include <libcalc.hpp>

namespace libcalc {

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

Tokenizer::Tokenizer() { }

Tokenizer::~Tokenizer() {
  clear();
}

Tokenizer::Tokenizer(std::string expression) {
  parse(expression);
}

void Tokenizer::parse(std::string expression) {
  for (char e : expression) {
    tokens.push_back(new Token(e));
  }
}

void Tokenizer::clear() {
  for (Token *t : tokens) {
    delete t;
  }

  tokens.clear();
}

}
