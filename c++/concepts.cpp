#include <iterator>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

template<typename T, typename U = T>
concept Number =
  requires(T x, U y) {   // Something with arithmetic operations and a zero
    x+y; x-y; x*y; x/y;
    x+=y; x-=y; x*=y; x/=y;
    x=x;         // copy
    x=0;
  };

template<typename T, typename U = T>
concept Arithmetic = Number<T,U> && Number<U,T>;

template<forward_iterator Iter, Arithmetic<iter_value_t<Iter>> Val>
auto accumulate(Iter first, Iter last, Val res) -> Val {
  for (auto p = first; p!=last; ++p)
    res += *p;
  return res;
}

int main() {
  {
  list a {4.f, 5.f, 6.f};
  auto res = accumulate(a.begin(), a.end(), 0);
  cout << res << endl;
  }

  /*
  {
  unordered_map<string, int> a = {{"wow"s, 5}};
  auto res = accumulate(a.begin(), a.end(), 0);
  cout << res << endl;
  }
  */

  {
  auto a {"a"s};
  auto res = accumulate(a.begin(), a.end(), 0);
  cout << hex << showbase << res << endl;
  }

  {
  vector a {4, 19, 3};
  auto res = accumulate(a.begin(), a.end(), 0);
  cout << dec << res << endl;
  }

  return 0;
}
