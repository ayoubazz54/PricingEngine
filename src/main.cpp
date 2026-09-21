#include <iostream>
#include "../include/option.hpp"
#include "../include/black_sholes.hpp"
#include "../include/greeks.hpp"
#include "../include/crr.hpp"
#include "../include/monte_carlo.hpp"
#include "../include/monte_carlo_parallel.hpp"


int main() {
    parameters par;
    par.S0 = 100;
    par.K = 100;
    par.T = 1;
    par.r = 0.05;
    par.sigma = 0.20;

    int n = 50;
    int M;
    unsigned long long seed = 12345;

    Option C(par, typeoption::CALL);
    Option P(par, typeoption::PUT);

    long double priceC_BS = BlackSholes::price(C);
    long double priceP_BS = BlackSholes::price(P);

    std::cout << "Black-Sholes model: " << std::endl;
    std::cout << "  Le prix de l'option call est: "
    << priceC_BS << ". " << std::endl;

    std::cout << "  Le prix de l'option put est: "
    << priceP_BS << ". " << std::endl;

    std::cout << "  L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_BS, priceP_BS) << std::endl;

    std::cout << "Maintenant calculant les greeks," << std::endl;

    std::cout << "  Call: " << std::endl;

    std::cout << "      Delta: " << Greeks::deltaC(C) 
    << ", Gamma: " << Greeks::gamma(C)
    << ", Theta: " << Greeks::thetaC(C) 
    << ", Vega: " << Greeks::vega(C)
    << ", Rho: " << Greeks::rhoC(C) << std::endl;

    std::cout << "  Put: " << std::endl;

    std::cout << "      Delta: " << Greeks::deltaP(P)
    << ", Gamma: " << Greeks::gamma(P)
    << ", Theta: " << Greeks::thetaP(P) 
    << ", Vega: " << Greeks::vega(P)
    << ", Rho: " << Greeks::rhoP(P) << std::endl;


    // pour le modèle binomiale:
    std::cout << "Cox-Ross-Rubinstein model: " << std::endl;
    std::cout << "La taille de l'arbre binomiale des prix: ";
    std::cin >> n;
    
    long double priceC_CRR = CRR::price(C, n);
    long double priceP_CRR = CRR::price(P, n);

    std::cout << "  Le prix de l'option call est: "
    << priceC_CRR << ". " << std::endl;

    std::cout << "  Le prix de l'option put est: "
    << priceP_CRR << ". " << std::endl;

    std::cout << "  L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_CRR, priceP_CRR) << std::endl;

    std::cout << "  L'erreur Vbs - Vccr (Call): "
    << priceC_BS - priceC_CRR << std::endl;

    std::cout << "  L'erreur Vbs - Vccr (put): "
    << priceP_BS - priceP_CRR << std::endl;

    // pour le modèle monte carlo:
    std::cout << "using Monte Carlo: " << std::endl;
    std::cout << "Le nombre des échantillons: " ;
    std::cin >> M;
    
    MonteCarloResult resultC_MC = MonteCarlo::price(C, M, seed);
    MonteCarloResult resultP_MC = MonteCarlo::price(P, M, seed);

    long double priceC_MC = resultC_MC.price;
    long double priceP_MC = resultP_MC.price;

    std::cout << "  Le prix de l'option call est: "
    << priceC_MC << ". " << std::endl;

    std::cout << "  Le prix de l'option put est: "
    << priceP_MC << ". " << std::endl;

    std::cout << "  L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_MC, priceP_MC) << std::endl;

    std::cout << "  L'erreur Vbs - Vmc (Call): "
    << priceC_BS - priceC_MC << std::endl;

    std::cout << "  L'erreur standard pour Call: "
    << resultC_MC.standardError << std::endl;

    std::cout << "  L'intervalle de confiance pour Call: ["
    << resultC_MC.confidenceHigh << ", " << resultC_MC.confidenceLow << "]" << std::endl;

    std::cout << "  L'erreur Vbs - Vmc (put): "
    << priceP_BS - priceP_MC << std::endl;

    std::cout << "  L'erreur standard pour Put: "
    << resultC_MC.standardError << std::endl;

    std::cout << "  L'intervalle de confiance pour Put: ["
    << resultC_MC.confidenceHigh << ", " << resultC_MC.confidenceLow << "]" << std::endl;

    // pour le modèle monte carlo parallel:
    std::cout << "using Monte Carlo Parallel: " << std::endl;
    std::cout << "Le nombre des échantillons: " ;
    std::cin >> M;
    
    MonteCarloResult resultC_MCP = MonteCarloParallel::price(C, M, seed, 4);
    MonteCarloResult resultP_MCP = MonteCarloParallel::price(P, M, seed, 4);

    long double priceC_MCP = resultC_MCP.price;
    long double priceP_MCP = resultP_MCP.price;

    std::cout << "  Le prix de l'option call est: "
    << priceC_MCP << ". " << std::endl;

    std::cout << "  Le prix de l'option put est: "
    << priceP_MCP << ". " << std::endl;

    std::cout << "  L'erreur du calcul (C - P) - (S0 - Ke^(-rT)): "
    << BlackSholes::errorCP(C, priceC_MCP, priceP_MCP) << std::endl;

    std::cout << "  L'erreur Vbs - Vmc (Call): "
    << priceC_BS - priceC_MCP << std::endl;

    std::cout << "  L'erreur standard pour Call: "
    << resultC_MCP.standardError << std::endl;

    std::cout << "  L'intervalle de confiance pour Call: ["
    << resultC_MCP.confidenceHigh << ", " << resultC_MCP.confidenceLow << "]" << std::endl;

    std::cout << "  L'erreur Vbs - Vmc (put): "
    << priceP_BS - priceP_MCP << std::endl;

    std::cout << "  L'erreur standard pour Put: "
    << resultC_MCP.standardError << std::endl;

    std::cout << "  L'intervalle de confiance pour Put: ["
    << resultC_MCP.confidenceHigh << ", " << resultC_MCP.confidenceLow << "]" << std::endl;
}