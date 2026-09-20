#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "option.hpp"


class MonteCarlo {
    public:

        struct MonteCarloResult {
            long double price;
            long double standardError;
            long double confidenceLow;
            long double confidenceHigh;
        };
        typedef struct MonteCarloResult MonteCarloResult;

        static MonteCarloResult price(const Option& option, int M, unsigned long long seed);

};


#endif