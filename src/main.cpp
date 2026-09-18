#include <iostream>
#include "../include/option.hpp"
#include "../include/black_sholes.hpp"
#include "../include/greeks.hpp"
#include "../include/crr.hpp"

int main() {
    parameters par;
    par.S0 = 100;
    par.K = 100;
    par.T = 1;
    par.r = 0.05;
    par.sigma = 0.20;

    int n = 50;

    Option C = Option(par, typeoption::CALL);
    Option P = Option(par, typeoption::PUT);

    long double priceC_BS = BlackSholes::price(C);
    long double priceP_BS = BlackSholes::price(P);

    std::cout << "Black-Sholes model: " << std::endl;
    std::cout << "Le prix de l'option call est: "
    << priceC_BS << ". " << std::endl;

    std::cout << "Le prix de l'option put est: "
    << priceP_BS << ". " << std::endl;

    std::cout << "L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_BS, priceP_BS) << std::endl;

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


    // pour le modèle binomiale:
    std::cout << "Cox-Ross-Rubinstein model: " << std::endl;
    std::cin >> n;
    
    long double priceC_CRR = CRR::price(C, n);
    long double priceP_CRR = CRR::price(P, n);

    std::cout << "Le prix de l'option call est: "
    << priceC_CRR << ". " << std::endl;

    std::cout << "Le prix de l'option put est: "
    << priceP_CRR << ". " << std::endl;

    std::cout << "L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_CRR, priceP_CRR) << std::endl;

    std::cout << "L'erreur Vbs - Vccr (Call): "
    << priceC_BS - priceC_CRR << std::endl;

    std::cout << "L'erreur Vbs - Vccr (put): "
    << priceP_BS - priceP_CRR << std::endl;
}