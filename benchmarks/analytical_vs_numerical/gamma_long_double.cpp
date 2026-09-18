#include <iostream>
#include <cmath>
#include <iomanip>
#include "../../include/option.hpp"
#include "../../include/greeks.hpp"
#include "../../include/black_sholes.hpp"



int main() {
    parameters par1;
    par1.S0 = 100;
    par1.K = 100;
    par1.T = 1;
    par1.r = 0.05;
    par1.sigma = 0.20;

    Option C1 = Option(par1, typeoption::CALL);
    long double gammaAnalytic = Greeks::gamma(C1);

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Gammas analytique: " << gammaAnalytic << std::endl;
    std::cout << "Gammas numeriques: " << std::endl;

    long double V = BlackSholes::price(C1);
    long double h;
    long double gammaNumeric;
    parameters par2 = par1;
    long double V1, V2;

    for (int i = 1; i < 15; i++) {
        h = pow(10, -i);
        par1.S0 = 100 + h;
        par2.S0 = 100 - h;
        V1 = BlackSholes::price(Option(par1, typeoption::CALL));
        V2 = BlackSholes::price(Option(par2, typeoption::CALL));

        gammaNumeric = (V1 - 2*V + V2) / (h * h);

        std::cout << "h = " << h << ", gamma = " <<  gammaNumeric
        << ", l'erreur = " << gammaNumeric - gammaAnalytic
        << std::endl;
    }
}