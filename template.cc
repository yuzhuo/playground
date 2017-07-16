
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

void func1(int x)
{
    cout << x << endl;
}

void func2(int x, int y)
{
    cout << x << ", " << y << endl;
}

void func3(int x, int y, int z)
{
    cout << x << ", " << y << ", " << z << endl;
}

class Closure
{
public:
    Closure() {}
    virtual ~Closure() {}

    virtual void run() = 0;
};

template <typename... T>
class VariadicArgsClosure : public Closure
{
    using bind_type = decltype(std::bind(std::declval<std::function<void(T...)>>(), std::declval<T>()...));
  
public:


    template <typename... ConstrT>
    VariadicArgsClosure(std::function<void(T...)> f, ConstrT&&... args)
        : Closure()
        , bind_(f, std::forward<ConstrT>(args)...)
    { }

    virtual void run() 
    { bind_(); }

private:
    bind_type bind_;
};




//template<typename R, typename ...A>
//R test(R f(A...), A...params)
//{
    //cout << f(params...) << endl;
//}

int main()
{
    vector<Closure*> funcs;
    VariadicArgsClosure<int> vf1(func1, 1);
    VariadicArgsClosure<int, int> vf2(func2, 1, 2);
    VariadicArgsClosure<int, int, int> vf3(func3, 1, 2, 3);
    funcs.push_back(&vf1);
    funcs.push_back(&vf2);
    funcs.push_back(&vf3);

    for (int i = 0; i < funcs.size(); ++i)
    {
        funcs[i]->run();
    }
    
    //test(func1, 1);
    //test(func2, 1, 2);
    //test(func3, 1, 2, 3);

    return 0;
}
