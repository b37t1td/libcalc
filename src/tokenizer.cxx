#include <libcalc.hpp>

#include <stack>

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

std::vector<Token *> Tokenizer::toRPN() {
  std::vector<Token *> rpn;
  std::stack<Token *> op;

  for (auto t : tokens) {
    if (t->type != TOKEN_TYPE.OPERATOR) {
      rpn.push_back(t);
      continue;
    } else if (t->value == "+" || t->value == "-") {

        while( !op.empty() &&
            (op.top()->value == "-" ||
             op.top()->value == "+" ||
             op.top()->value == "*" ||
             op.top()->value == "/" ||
             op.top()->value == "%" ||
             op.top()->value == "!" ||
             op.top()->value == "^" )) {

          rpn.push_back(op.top());
          op.pop();
        }

        op.push(t);

    } else if (t->value == "*" || t->value == "/") {

        while( !op.empty() &&
            (op.top()->value == "*" ||
             op.top()->value == "/" ||
             op.top()->value == "%" ||
             op.top()->value == "!" ||
             op.top()->value == "^" )) {

          rpn.push_back(op.top());
          op.pop();
        }
        op.push(t);

    } else if (t->value == "(" ||
               t->value == "^" ||
               t->value == "%" ||
               t->value == "!") {

      op.push(t);

    } else if (t->value == ")") {
      while (!op.empty() && op.top()->value != "(") {
        rpn.push_back(op.top());
        op.pop();
      }
      op.pop();
    }
  }

  while(!op.empty()) {
    rpn.push_back(op.top());
    op.pop();
  }

  return rpn;
}

double Tokenizer::evaluate() {
  std::stack<double> temp;
  double l, a, r;
  char o;

  for (Token *t : toRPN()) {
    if (t->type == TOKEN_TYPE.OPERATOR) {

      r = temp.top();
      temp.pop();

      o = t->value.c_str()[0];

      l = temp.top();
      temp.pop();

      switch(o) {
        case '+': a =  l + r ; break;
        case '-': a =  l - r ; break;
        case '*': a =  l * r ; break;
        case '/': a =  l / r ; break;
        case '%': a =  (int)l % (int) r ; break;
        case '^': a =  (int)l ^ (int)r ; break;
        case '!': a =  factorial(r) ; break;
      }

      temp.push(a);

    } else {
      temp.push(std::atof(t->value.c_str()));
    }
  }

  return temp.top();
}

}
