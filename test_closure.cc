
#include <iostream>
#include <functional>
#include <utility>
using namespace std;

int func1(int a1)
{
    return a1;
}

int func2(int a1, int a2)
{
    return a1;
}

int func3(int a1, int a2, int a3)
{
    return a1;
}

int func4(int a1, int a2, int a3, int a4)
{
    return a1;
}

struct FuncObj1
{
    int operator()(int a1)
    {
        return a1;
    }
};

struct FuncObj2
{
    int operator()(int a1, int a2)
    {
        return a1 + a2;
    }
};

class Test
{
public:
    Test() {}

    static int test(int a1)
    {
        return a1;
    }
};

template<typename Func, typename ...Args>
class Closure
{
    using bind_type = decltype(bind(declval<Func>(), declval<Args>()...));
public:
    Closure(Func f, Args ...args)
        : func_(bind(f, args...))
    {
    }

    void operator()()
    {
        cout << func_() << endl;
    }

private:
    const bind_type& func_;
};

template<typename Func, typename ...Args>
Closure<Func, Args...>
make_closure(Func f, Args ...args)
{
    return Closure<Func, Args...>(f, args...);
}

int main()
{
    //auto f1 = bind(func1, 1);
    //cout << f1() << endl;
    
    //auto f2 = bind(func2, 1, 2);
    //cout << f2() << endl;

    //auto f3 = bind(func3, 1, 2, 3);
    //cout << f3() << endl;

    //auto f4 = bind(func4, 1, 2, 3, 4);
    //cout << f4() << endl;

    //auto fo1 = bind(FuncObj1(), 10);
    //cout << fo1() << endl;

    //auto fo2 = bind(FuncObj2(), 10, 20);
    //cout << fo2() << endl;

    //auto l1 = bind([](int a1) { return a1; }, 100);
    //cout << l1() << endl;

    //auto l2 = bind([](int a1, int a2) { return a1; }, 100, 200);
    //cout << l2() << endl;

    //auto s1 = bind(Test::test, 1000);
    //cout << s1() << endl;

    Closure<int(*)(int), int> c1(func1, 1000);
    c1();

    auto c2 = make_closure(func1, 1);
    c2();

    return 0;
}

