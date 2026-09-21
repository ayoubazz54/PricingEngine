#ifndef MONTE_CARLO_PARALLEL_HPP
#define MONTE_CARLO_PARALLEL_HPP

#include "option.hpp"
#include "monte_carlo.hpp"


class MonteCarloParallel {
    public:

        static MonteCarloResult price(const Option& option, int M, unsigned long long seed, int numThreads);

};


#endif