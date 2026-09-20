#include "../../include/crr.hpp"
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

    std::vector<int> numbersOfSteps = { 100, 1000, 10000, 100000 };
    std::ofstream file("crr_convergence.csv");

    if (!file.is_open()) {
        std::cerr << "Error during CSV file opening\n";
        return 1;
    }

    file << "n,price,error,time\n";

    std::cout << std::fixed << std::setprecision(10);

    for (int n : numbersOfSteps) {

        auto start = std::chrono::high_resolution_clock::now();
        long double priceCRR = CRR::price(option, n);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;

        long double error = fabs(priceCRR - exactPrice);

        file << n << ","
             << priceCRR << ","
             << error << ","
             << elapsed.count() << "\n";

        std::cout 
            << "n = " << n
            << " Price = " << priceCRR
            << " Error = " << error 
            << " Time = " << elapsed.count() << "s\n";

    }

    file.close();

    std::cout << "\nCSV generated: crr_convergence.csv\n";

    return 0;

}