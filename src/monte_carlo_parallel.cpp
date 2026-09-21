#include "../include/monte_carlo_parallel.hpp"
#include <cmath>
#include <random>

// OpenMP Library
#include <omp.h>

MonteCarloResult MonteCarloParallel::price(const Option& o, int M, unsigned long long seed, int numThreads) {
    MonteCarloResult result;

    bool isCall = o.getType() == typeoption::CALL;
    const long double S0 = o.getS0();
    const long double K = o.getK();
    const long double r = o.getR();
    const long double sigma = o.getSigma();
    const long double T = o.getT();

    const long double sqrtT = std::sqrt(T);
    const long double discount = exp(-r * T);
    const long double drift = (r - 0.5L * sigma * sigma) * T;
    const long double diffusion = sigma * sqrtT;

    long double variance = 0.0L;
    long double mean = 0.0L;

    #pragma omp parallel num_threads(numThreads)
    {
        std::mt19937_64 generator(seed + omp_get_thread_num());
        std::normal_distribution<long double> distribution(0.0L, 1.0L);

        long double localSum = 0.0L;
        long double localSumSquared = 0.0L;

        #pragma omp for
        for (int i = 0; i < M; i++) {
            long double payoff;
            long double Z = distribution(generator);
            long double S = S0 * exp(drift + diffusion * Z);

            if (o.getType() == typeoption::CALL) {
                payoff = std::max(S - K, 0.0L);
            }
            else {
                payoff = std::max(K - S, 0.0L);
            }
            
            long double X = discount * payoff;

            localSum += X;
            localSumSquared += X * X;
        }

        #pragma omp atomic
        mean += localSum;

        #pragma omp atomic
        variance += localSumSquared;
    }
    mean = mean / M;
    variance = (variance - M * mean * mean) / (M - 1);

    result.price = mean;
    result.standardError = sqrt(variance / M);
    result.confidenceHigh = result.price + 1.96L * result.standardError;
    result.confidenceLow = result.price - 1.96L * result.standardError;

    return result;
    

}
