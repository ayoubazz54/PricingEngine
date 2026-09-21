#include "../../include/monte_carlo_parallel.hpp"
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
#include <string>
#include <fstream>
#include <random>


int main() {

    
    parameters par = {100.0L, 100.0L, 0.05L, 0.2L, 1.0L};
    Option option(par, typeoption::CALL);

    long double exactPrice = BlackSholes::price(option);

    std::vector<int> simulations = { 1000, 10000, 100000, 1000000, 10000000, 100000000};
    std::vector<int> numThreads = { 1, 2, 4, 8, 12 };
    for (int i : numThreads) {
        std::ofstream file("monte_carlo_convergence_parallel_" + std::to_string(i) + ".csv");

        if (!file.is_open()) {
            std::cerr << "Error during CSV file opening\n";
            return 1;
        }

        file << "thread,M,price,standard_error,error,ci_low,ci_high,time\n";

        const uint64_t seed = 156;

        std::cout << std::fixed << std::setprecision(10);

        for (int M : simulations) {

            auto start = std::chrono::high_resolution_clock::now();
            MonteCarloResult result = MonteCarloParallel::price(option, M, seed, i);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;

            long double error = fabs(result.price - exactPrice);

            file << i << "," 
                << M << ","
                << result.price << ","
                << result.standardError << "," 
                << error << ","
                << result.confidenceLow << ","
                << result.confidenceHigh << ","
                << elapsed.count() << "\n";

            std::cout 
                << "M = " << M
                << " Price = " << result.price 
                << " SE = " << result.standardError 
                << " Error = " << error 
                << " Time = " << elapsed.count() << "s\n";

        }

        file.close();

        std::cout << "\nCSV generated: monte_carlo_convergence_" + std::to_string(i) + ".csv\n";
    }

    return 0;

}