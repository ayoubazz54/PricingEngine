#include "../include/monte_carlo.hpp"
#include <cmath>
#include <random>

MonteCarloResult MonteCarlo::price(const Option& o, int M, unsigned long long seed) {
    MonteCarloResult result;

    std::mt19937_64 generator(seed);
    std::normal_distribution<long double> distribution(0.0L, 1.0L);

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
        
        mean += discount * payoff;
    }

    for (int i = 0; i < M; i++) {
        long double payoff;
        long double Z = distribution(generator);
        long double S = S0 * exp(drift + diffusion * Z);

        if (isCall) {
            payoff = std::max(S - K, 0.0L);
        }
        else {
            payoff = std::max(K - S, 0.0L);
        }
        
        variance += pow(discount * payoff - mean, 2) / (M - 1);
    }

    result.price = mean / M;
    result.standardError = sqrt(variance / M);
    result.confidenceHigh = result.price + 1.96L * result.standardError;
    result.confidenceLow = result.price - 1.96L * result.standardError;

    return result;
    

}
