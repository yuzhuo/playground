
#include <iostream>
#include <unistd.h>

class Date
{
public:
    Date(int y, int m, int d)
        : year_(y)
        , month_(m)
        , day_(d)
    {
    }

    int get_year() const
    {
        return year_;
    }

    int get_month() const
    {
        return month_;
    }

    int get_day() const
    {
        return day_;
    }

private:
    int year_;
    int month_;
    int day_;
};

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << "Date: " << "year: " << date.get_year() << ", month: " << date.get_month()
        << ", day: " << date.get_day() << std::endl;
    return os;
}


int main()
{
    Date d(2017, 10, 7);
    std::cout << d;
    std::cout << "main thread id: " << pthread_self() << std::endl;

    return 0;
}

