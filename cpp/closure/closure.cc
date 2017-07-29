
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


class Closure
{
public:
    Closure() {}
    virtual ~Closure() {}

    virtual void run() = 0;
};

template <typename R, typename... T>
class VariadicArgsClosure : public Closure
{
public:

  using bind_type = decltype(std::bind(std::declval<std::function<R(T...)>>(),std::declval<T>()...));

  VariadicArgsClosure(std::function<R(T...)> f, T&&... args)
    : bind_(f, std::forward<T>(args)...)
  {
  }

  virtual void run() 
  { 
      bind_();
  }

private:
  bind_type bind_;
};

template <typename R, typename... T, typename... Args>
VariadicArgsClosure<R, T...>
make_closure(R(*f)(T...), Args&&... args)
{
    return VariadicArgsClosure<R, T...>(f, std::forward<Args>(args)...);
}

char func1(int, double)
{
    cout << "func1" << endl;
    return '7';
}

string func2(int)
{
    cout << "func2" << endl;
    return "fuck";
}

struct Pair
{
    Pair(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    int x;
    int y;
    int z;
};

Pair func3(int x, int y, int z)
{
    cout << "func3" << endl;
    return Pair(x, y, z);
}

int main()
{
    vector<Closure*> vec;
    auto c1 = make_closure(func1, 1.0, 1.0);
    vec.push_back(&c1);

    auto c2 = make_closure(func2, 1.0);
    vec.push_back(&c2);
    
    auto c3 = make_closure(func3, 1.0, 2.0, 3.0);
    vec.push_back(&c3);

    for (int i = 0; i < vec.size(); ++i) {
        vec[i]->run();
    }

    return 0;
}
