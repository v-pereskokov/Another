#include <iostream>
#include <fstream>

#define methods
#define enums
#define params

class DeleterCommentsC {
  private enums:
  enum class State {
    Basic = 1,
    Quotes,
    Slash,
    IgnoreQuote,
    IgnoreSlash
  };
  
  public methods:
  DeleterCommentsC(std::istream *, std::ostream *);
  
  void deleteComments();
  
  private methods:
  DeleterCommentsC() = delete;
  
  State isBasicState(const char, DeleterCommentsC::State);
  
  void slash(char);
  
  void quote(char);
  
  void doubleSlash(State);
  
  void slashStar(State);
  
  private params:
  std::istream *_in;
  std::ostream *_out;
  State _state;
};

DeleterCommentsC::DeleterCommentsC(std::istream *in, std::ostream *out)
: _in(in), _out(out), _state(DeleterCommentsC::State::Basic) {}

void DeleterCommentsC::deleteComments() {
  char symbol;
  while (!_in->eof()) {
    _in->get(symbol);
    switch (_state) {
      case DeleterCommentsC::State::Basic:
        _state = isBasicState(symbol, _state);
        break;
      case DeleterCommentsC::State::Slash:
        slash(symbol);
        break;
      case DeleterCommentsC::State::Quotes:
        quote(symbol);
        break;
    }
  }
}

DeleterCommentsC::State DeleterCommentsC::isBasicState(const char symbol, DeleterCommentsC::State state) {
  switch (symbol) {
    case '"':
    case ''':
      _in.put(symbol);
      return DeleterCommentsC::State::Quotes;
    case '/':
      return DeleterCommentsC::State::Slash;
    default:
      _out->put(symbol);
      return state;
  }
}

void DeleterCommentsC::slash(char symbol) {
  char prevSymbol = symbol;
  _in->get(symbol);
  switch (symbol) {
    case '/':
      _state = DeleterCommentsC::State::IgnoreQuote;
      doubleSlash(_state);
      break;
    case '*':
      _state = DeleterCommentsC::State::IgnoreSlash;
      slashStar(_state);
      break;
    default:
      _out->put(prevSymbol);
      _out->put(symbol);
      break;
  }
}

void DeleterCommentsC::quote(const char quote, DeleterCommentsC::State state) {
  char symbol;
  while (state == DeleterCommentsC::State::IgnoreQuote) {
    _in->get(symbol);
    _out->put(symbol);
    if (symbol == '\\') {
      _in->get(symbol);
      _out->put(symbol);
    }
    else if (symbol == quote) {
      state = DeleterCommentsC::State::Basic;
    }
  }
}

void DeleterCommentsC::doubleSlash(DeleterCommentsC::State state) {
  char symbol;
  while (state == DeleterCommentsC::State::IgnoreSlash) {
    _in->get(symbol);
    if (symbol == '\n') {
      *_out << symbol;
      state = DeleterCommentsC::State::Basic;
    }
  }
}

void DeleterCommentsC::slashStar(DeleterCommentsC::State state) {
  char symbol;
  while (state == DeleterCommentsC::State::IgnoreQuote) {
    _in->get(symbol);
    if (symbol == '*') {
      _in->get(symbol);
      if (symbol == '/') {
        state = DeleterCommentsC::State::Basic;
      }
    }
  }
}

int main () {
  std::ifstream in("test.txt");
  std::ofstream out("output.txt");
  DeleterCommentsC temp(&in, &out);
  temp.deleteComments();
  return 0;
}
