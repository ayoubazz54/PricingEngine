#ifndef GREEKS_HPP
#define GREEKS_HPP
#include "option.hpp"
#include "black_sholes.hpp"

class Greeks {
    public: 
        /* La densité de la loi normale. */
        static double phi(double);

        static double deltaC(const Option&);

        static double deltaP(const Option&);

        static double gamma(const Option&);

        static double vega(const Option&);

        static double rhoC(const Option&);

        static double rhoP(const Option&);

        static double thetaC(const Option&);

        static double thetaP(const Option&);

};




#endif