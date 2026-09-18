#ifndef CRR_HPP
#define CRR_HPP

#include "option.hpp"


class CRR {
    public:

        static long double putPrice(const Option&, int n);

        static long double callPrice(const Option&, int n);

        static long double price(const Option&, int n);

};


#endif