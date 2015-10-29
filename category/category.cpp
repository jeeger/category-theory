#include <iostream>
#include <cmath>
#include <functional>
#include <cstdlib>
#include <limits>
using namespace std;

#define GCC_VERSION (__GNUC__ * 100		\
		     + __GNUC_MINOR__) 
#if GCC_VERSION > 409
#define GCC_VERYNEW
#endif


#ifndef GCC_VERYNEW

/*
 * The first version, with explicit template instantiations
 */
template<class A, class B, class C> function<C(A)> compose(function<B(A)> one, function<C(B)> two) {
  return [one, two](A val) -> C {
    auto result1 = one(val);
    return two(result1);
  };
}

template<class A> A identity(A val) {
  return val;
}

#endif


#ifdef GCC_VERYNEW

/*
 * Second shorter version, won't compile with gcc < 4.9
 * Modified from http://gcc.godbolt.org/#%7B%22version%22%3A3%2C%22filterAsm%22%3A%7B%22labels%22%3Atrue%2C%22directives%22%3Atrue%2C%22commentOnly%22%3Atrue%7D%2C%22compilers%22%3A%5B%7B%22sourcez%22%3A%22MQSwdgxgNgrgJgUwAQB4YBcRROgngPgChCBDDAeyQnLAGd0kQ4kBeJAbQF0AKM9cgGQCk6AJRIAtPiSJoeAA4JuYoUgDeSAE4J0MTWCT04ALmMAzcpoDuJTXBSyoCpWPzLRAbiQBfD8XQIALbyUCQBKM5gJIHIAOIANCK4ilExSABiRHyU5IqaYZYAVNyxqgDmiemqZuIa2rr6HBVmPNmqYupaOnoGZdxm3EamFta29o7O7m5iop4%2BXt7EAPRLSACqtCRlyJvBUAjE2VQ09EhmrBw84AwAbrVdDQY3kkgAjAB0Zgt%2BR9R0DGULlx%2BlByGEkHdOvUeoZ0GEQBAAPoQEj0FDXNx3b6kCjHf5IMqIkhmAKaRHnNiAwpnPyEa5IQIkcDcem2MoQRIQAAWtkK1LZkLUhCQDxh3CpZyQ1KYom4r08hEWQAAA%3D%3D%22%2C%22compiler%22%3A%22%2Fopt%2Fgcc-4.9.0%2Fbin%2Fg%2B%2B%22%2C%22options%22%3A%22-O2%20-std%3Dc%2B%2B1y%22%7D%5D%7D
 */

auto identity = [](auto t) -> decltype(t) {return t;};
// C++1y allows inference of lambda return type when the only
// statement in the lambda is a return statement.
template <class F, class G> auto compose(F one, G two) {
  return [=](auto t) { return one(two(t));}};

#endif

//Test for ints
void testIdentity() {
  auto limits = numeric_limits<int>();
  auto composed = compose(function<int(int)>(identity<int>),
			  function<int(int)>(identity<int>));
  for (int i = limits.min(); i < limits.max(); i++) {
    if (identity(i) != composed(i)) {
      cout << "Error for value " << i << ". Identity returned " << identity(i);
      cout << ", composed returned " << composed(i) << endl;
    }
  }
}

int main() {
  // Don't run this, it'll take long.
  testIdentity();
  return 0;
}
