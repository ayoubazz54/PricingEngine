#ifndef GREEKS_HPP
#define GREEKS_HPP
#include "option.hpp"
#include "black_sholes.hpp"

class Greeks {
    public: 
        /* La densité de la loi normale. */
        static long double phi(long double);

        static long double deltaC(const Option&);

        static long double deltaP(const Option&);

        static long double gamma(const Option&);

        static long double vega(const Option&);

        static long double rhoC(const Option&);

        static long double rhoP(const Option&);

        static long double thetaC(const Option&);

        static long double thetaP(const Option&);

};




#endif