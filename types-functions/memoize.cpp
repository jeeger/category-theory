#include <iostream>
#include <cmath>
#include <functional>
#include <cstdlib>
#include <limits>
#include <map>

using namespace std;

template<class A, class B> class Memoizer {

public:
  Memoizer(function<A(B)> tomemoize);
  B operator()(A arg);

private:
  map<A, B> memoized;
  function<A(B)> fun;
};

template<class A, class B> Memoizer<A,B>::Memoizer(function<A(B)> tomemoize) {
  fun = tomemoize;
  memoized = map<A, B>();
}

template<class A, class B> B Memoizer<A,B>::operator()(A arg) {
  auto place = memoized.find(arg);
  if (place == memoized.end()) {
    // Ack
    cout << "Set memoized arg" << endl; 
    return (memoized[arg] = fun(arg));
  } else {
    cout << "Read memoized arg" << endl;
    return place->second;
  }
}

// Recursive functions are a bit harder to memoize.
int main() {
  // We need the ugly cast to get the right version of sqrt.
  auto memoized = Memoizer<double, double>
    (static_cast<double (*)(double)>(sqrt));
  cout << memoized(3) << endl;
  cout << memoized(9) << endl;
  cout << memoized(3) << endl;
  return 0;
}
