
#include <algorithm>
#include <memory>
#include <iostream>
#include <stdio.h>
using namespace std;


template <typename R, typename... T>
class Test
{
public:

  using bind_type = decltype(std::bind(std::declval<std::function<R(T...)>>(),std::declval<T>()...));

  Test(std::function<R(T...)> f, T&&... args)
    : bind_(f, std::forward<T>(args)...)
  {
      cout << "VariadicArgsClosure" << endl;
  }

private:
  bind_type bind_;
};

struct Data
{
    // Data() { }
    Data(int d) { }

    int dummy_;
};

Data func(int)
{
    return Data(1);
}

int main()
{
    Test<Data, int> test(func, 1);

    return 0;
}
