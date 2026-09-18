#include "../include/greeks.hpp"
#include <cmath>


long double Greeks::phi(long double x) {
    return exp(- x*x/2) / sqrt(2 * 3.141592);
}

long double Greeks::deltaC(const Option& o) {
    return BlackSholes::N(BlackSholes::d1(o));
}

long double Greeks::deltaP(const Option& o) {
    return deltaC(o) - 1;
}

long double Greeks::gamma(const Option& o) {
    return phi(BlackSholes::d1(o)) / (o.getS0() * o.getSigma() * sqrt(o.getT()));
}

long double Greeks::vega(const Option& o) {
    return o.getS0() * phi(BlackSholes::d1(o)) * sqrt(o.getT());
}

long double Greeks::rhoC(const Option& o) {
    return o.getK() * o.getT() * exp(- o.getR() * o.getT()) * BlackSholes::N(BlackSholes::d2(o));
}

long double Greeks::rhoP(const Option& o) {
    return - o.getK() * o.getT() * exp(- o.getR() * o.getT()) * BlackSholes::N( - BlackSholes::d2(o));
}

long double Greeks::thetaC(const Option& o) {
    return - o.getS0() * phi(BlackSholes::d1(o)) * o.getSigma() / (2 * sqrt(o.getT()))
            - o.getR() * o.getK() * exp(- o.getR() * o.getT()) * BlackSholes::N(BlackSholes::d2(o));
}

long double Greeks::thetaP(const Option& o) {
    return - o.getS0() * phi(BlackSholes::d1(o)) * o.getSigma() / (2 * sqrt(o.getT()))
            + o.getR() * o.getK() * exp(- o.getR() * o.getT()) * BlackSholes::N( - BlackSholes::d2(o));
}