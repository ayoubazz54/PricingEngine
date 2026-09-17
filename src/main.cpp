#include <iostream>
#include "../include/option.hpp"
#include "../include/black_sholes.hpp"
#include "../include/greeks.hpp"

int main() {
    parameters par;
    par.S0 = 100;
    par.K = 100;
    par.T = 1;
    par.r = 0.05;
    par.sigma = 0.20;

    Option C = Option(par, typeoption::CALL);
    Option P = Option(par, typeoption::PUT);

    std::cout << "Le prix de l'option call est: "
    << BlackSholes::price(C) << ". " << std::endl;

    std::cout << "Le prix de l'option put est: "
    << BlackSholes::price(P) << ". " << std::endl;

    std::cout << "L'erreur du calcul: "
    << BlackSholes::errorCP(C, BlackSholes::price(C), BlackSholes::price(P)) << std::endl;

    std::cout << "Maintenant calculant les greeks," << std::endl;

    std::cout << "Call: " << std::endl;

    std::cout << "Delta: " << Greeks::deltaC(C) 
    << ", Gamma: " << Greeks::gamma(C)
    << ", Theta: " << Greeks::thetaC(C) 
    << ", Vega: " << Greeks::vega(C)
    << ", Rho: " << Greeks::rhoC(C) << std::endl;

    std::cout << "Put: " << std::endl;

    std::cout << "Delta: " << Greeks::deltaP(P)
    << ", Gamma: " << Greeks::gamma(P)
    << ", Theta: " << Greeks::thetaP(P) 
    << ", Vega: " << Greeks::vega(P)
    << ", Rho: " << Greeks::rhoP(P) << std::endl;

}