#ifndef BLACK_SHOLES_HPP
#define BLACK_SHOLES_HPP

#include "option.hpp"



class BlackSholes {
    public:
        static double N(double x);

        static double d1(const Option& option);

        static double d2(const Option& option);
        
        static double price(const Option& option);

};


#endif