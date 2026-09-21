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

    std::vector<int> numbersOfSteps = { 10, 25, 50, 101, 200, 351, 600, 1001, 2000, 4001, 7500, 15001, 30000 };
                                    
    std::ofstream file("crr_convergence.csv");

    if (!file.is_open()) {
        std::cerr << "Error during CSV file opening\n";
        return 1;
    }

    file << "n,price,error,time,exactprice\n";

    std::cout << std::fixed << std::setprecision(15);
    file << std::fixed << std::setprecision(15);

    for (int n : numbersOfSteps) {

        auto start = std::chrono::high_resolution_clock::now();
        long double priceCRR = CRR::price(option, n);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;

        long double error = fabs(priceCRR - exactPrice);

        file << n << ","
             << priceCRR << ","
             << error << ","
             << elapsed.count() << ","
             << exactPrice << "\n";

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