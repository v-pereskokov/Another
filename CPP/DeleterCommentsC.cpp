#include <fstream>
#include <map>

#define methods
#define params
#define enums

class DeleterCommentsC {
  typedef void (DeleterCommentsC::*ptr)();
  
  public methods:
  DeleterCommentsC(std::istream *, std::ostream *);
  
  void deleteComments();
  
  private enums:
  enum class State {
    Basic = 8,
    Quote = 0,
    Slash,
    Star,
    DoubleSlash,
    SlashStar
  };
  
  private methods:
  DeleterCommentsC() = delete;
  
  DeleterCommentsC(const DeleterCommentsC &) = delete;
  
  State whatState(const char);
  
  void quote();
  
  void slash();
  
  void doubleSlash();
  
  void slashStar();
  
  void init();
  
  private params:
  std::istream *_in;
  std::ostream *_out;
  std::map<State, ptr> _states;
  char _compare;
};

DeleterCommentsC::DeleterCommentsC(std::istream *in, std::ostream *out)
: _in(in), _out(out) {
  init();
}

void DeleterCommentsC::deleteComments() {
  char symbol;
  while (_in->get(symbol)) {
    State state = whatState(symbol);
    switch (state) {
      case State::Basic:
        _out->put(symbol);
        break;
      case State::Quote:
        _out->put(symbol);
        _compare = symbol;
        (this->*_states[state])();
        break;
      case State::Slash:
        (this->*_states[state])();
        break;
      default:
        _out->put(symbol);
        break;
    }
  }
}

DeleterCommentsC::State DeleterCommentsC::whatState(const char symbol) {
  switch (symbol) {
    case '\'':
    case '"':
      return State::Quote;
      break;
    case '/':
      return State::Slash;
      break;
    case '*':
      return State::Star;
    default:
      return State::Basic;
      break;
  }
}

void DeleterCommentsC::quote() {
  char symbol;
  while (_in->get(symbol)) {
    _out->put(symbol);
    if (symbol == '\\') {
      _in->get(symbol);
      _out->put(symbol);
    } else if (symbol == _compare) {
      break;
    }
  }
}

void DeleterCommentsC::slash() {
  char symbol;
  _in->get(symbol);
  State state = whatState(symbol);
  switch (state) {
    case State::Slash:
      (this->*_states[State::DoubleSlash])();
      break;
    case State::Star:
      (this->*_states[State::SlashStar])();
      break;
    default:
      _out->put('\\');
      _out->put(symbol);
  }
}

void DeleterCommentsC::doubleSlash() {
  char symbol;
  while (_in->get(symbol)) {
    if (symbol == '\\') {
      _in->get(symbol);
    } else if (symbol == '\n') {
      _out->put(symbol);
      break;
    }
  }
}

void DeleterCommentsC::slashStar() {
  char symbol;
  while (_in->get(symbol)) {
    if (symbol == '\\') {
      _in->get(symbol);
    } else if (symbol == '*') {
      _in->get(symbol);
      if (symbol == '/') {
        break;
      }
    }
  }
}

void DeleterCommentsC::init() {
  _states[State::Quote] = &DeleterCommentsC::quote;
  _states[State::Slash] = &DeleterCommentsC::slash;
  _states[State::DoubleSlash] = &DeleterCommentsC::doubleSlash;
  _states[State::SlashStar] = &DeleterCommentsC::slashStar;
}

int main () {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  DeleterCommentsC temp(&in, &out);
  temp.deleteComments();
  return 0;
}
