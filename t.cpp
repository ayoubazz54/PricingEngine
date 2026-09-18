#include <iostream>
#include <limits>

int main() {
    std::cout << "double precision      = "
              << std::numeric_limits<double>::digits10
              << '\n';

    std::cout << "long double precision = "
              << std::numeric_limits<long double>::digits10
              << '\n';
}