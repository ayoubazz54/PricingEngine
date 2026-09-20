#include "../../include/monte_carlo.hpp"
#include "../../include/black_sholes.hpp"

// for streaming
#include <iostream>
#include <iomanip>

// for creating and writing files
#include <fstream>

// for precise measurement of exceution time
#include <chrono>

#include <vector>
#include <cmath>


int main() {
    parameters par = {100.0L, 100.0L, 0.05L, 0.2L, 1.0L};
    Option option(par, typeoption::CALL);

    long double exactPrice = BlackSholes::price(option);

    std::vector<int> simulations = { 1000, 10000, 100000, 1000000, 10000000, 100000000};
    std::ofstream file("monte_carlo_convergence.csv");

    if (!file.is_open()) {
        std::cerr << "Error during CSV file opening\n";
        return 1;
    }

    file << "M,price,standard_error,error,ci_low,ci_high\n";

    const uint64_t seed = 42;

    std::cout << std::fixed << std::setprecision(10);

    for (int M : simulations) {

        auto start = std::chrono::high_resolution_clock::now();
        MonteCarloResult result = MonteCarlo::price(option, M, seed);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;

        long double error = fabs(result.price - exactPrice);

        file << M << ","
             << result.price << ","
             << result.standardError << "," 
             << error << ","
             << result.confidenceLow << ","
             << result.confidenceHigh << "\n";

        std::cout 
            << "M = " << M
            << " Price = " << result.price 
            << " SE = " << result.standardError 
            << " Error = " << error 
            << " Time = " << elapsed.count() << "s\n";

    }

    file.close();

    std::cout << "\nCSV generated: monte_carlo_convergence.csv\n";

    return 0;

}