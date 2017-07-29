
#ifndef __CLOSURE_H__
#define __CLOSURE_H__

#include <algorithm>
#include <memory>

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

    virtual void run() override
    { 
      bind_();
    }

private:
    bind_type bind_;
};

//template <typename R, typename... T, typename... Args>
//VariadicArgsClosure<R, T...>
//make_closure(R(*f)(T...), Args&&... args)
//{
    //return VariadicArgsClosure<R, T...>(f, std::forward<Args>(args)...);
//}

#endif /* __CLOSURE_H__ */
