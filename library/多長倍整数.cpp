#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;

int main()
{
    mp::cpp_int x = 1;

    for (unsigned int i = 1; i <= 100; ++i)
       x *= i;

    std::cout << x << std::endl;
}