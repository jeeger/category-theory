#include <iostream>
#include <cmath>
#include <functional>

using namespace std;


template<class A> class optional {
  bool _isValid;
  A _value;

public:
  optional() :_isValid(false) {}
  optional(A val) :_isValid(true), _value(val) {}
  bool isValid() { return _isValid; }
  A value() const { return _value; };
};

template<class T> ostream& operator<<(ostream& out, optional<T> arg) {
  if (arg.isValid()) {
    out << arg.value();
  } else {
    out << "not valid";
  }
  return out;
}

template<class A> optional<A> identity(A val) {
  return optional<A>(val);
}

template<class A, class B, class C> function<optional<C>(A)> compose(function<optional<B>(A)> f1, function<optional<C>(B)> f2) {
  return [f1, f2](A val) -> optional<C> {
    auto val1 = f1(val);
    if (val1.isValid())
      return f2(val1.value());
    else
      return val1;
  };
};

optional<double> safeRoot(double x) {
  if (x >= 0) return optional<double>(sqrt(x));
  else return optional<double>();
}

optional<double> safeReciprocal(double x) {
  if (x != 0) return optional<double>(1/x);
  else return optional<double>();
}

int main(int argc, char* argv[]) {
  auto composed = compose(function<optional<double>(double)>(safeRoot), function<optional<double>(double)>(safeReciprocal));

  cout << composed(0) << endl;
}
