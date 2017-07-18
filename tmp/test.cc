
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <cassert>
using namespace std;


void func1()
{
    throw 123;
}

void func2()
{
    int x = 10;
    func1();
}

void func3()
{
    func2();
}

enum LogLevel {
    kDebug,
    kInfo,
    kWarning,
    kError,
    kCritical,
};

class Test
{
public:
    Test()
    {
        cout << kDebug << endl;
    }

};

int main()
{
    cout << __func__ << endl;
    cout << __DATE__ << endl;
    cout << __TIME__ << endl;
    cout << __FILE__ << endl;
    cout << __cplusplus << endl;
    cout << __LINE__ << endl;
    cout << kDebug << endl;

    Test t;


    return 0;
}
