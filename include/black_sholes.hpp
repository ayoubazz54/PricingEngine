#ifndef BLACK_SHOLES_HPP
#define BLACK_SHOLES_HPP

#include "option.hpp"



class BlackSholes {
    public:
        static long double N(long double x);

        static long double d1(const Option& option);

        static long double d2(const Option& option);

        static long double putPrice(const Option& option);

        static long double callPrice(const Option& option);

        static long double price(const Option& option);

        static long double errorCP(const Option& option, long double C, long double P);
};


#endif