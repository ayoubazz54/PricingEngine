#include <cmath>
#include "../include/black_sholes.hpp"

using namespace std;


double BlackSholes::N (double x) {
    return (1 + erf(x / sqrt(2))) / 2;
}

double BlackSholes::d1(const Option& o) {
    return (log(o.getS0() / o.getK()) + (o.getR() + pow(o.getSigma(), 2)/2) * o.getT()) 
            / (o.getSigma() * sqrt(o.getT()));
}

double BlackSholes::d2(const Option& o) {
    return d1(o) - (o.getSigma() * sqrt(o.getT()));
}
        
double BlackSholes::price(const Option& o) {
    if (o.getType() == typeoption::CALL) {
        return o.getS0() * N(d1(o)) - o.getK() * exp(-o.getR() * o.getT()) * N(d2(o));
    }
    return o.getK() * exp(- o.getR() * o.getT()) * N(-d2(o)) - o.getS0() * N(-d1(o));
}
