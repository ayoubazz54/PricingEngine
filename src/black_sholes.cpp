#include <cmath>
#include "../include/black_sholes.hpp"

using namespace std;


long double BlackSholes::N (long double x) {
    return (1 + erf(x / sqrt(2))) / 2;
}

long double BlackSholes::d1(const Option& o) {
    return (log(o.getS0() / o.getK()) + (o.getR() + pow(o.getSigma(), 2)/2) * o.getT()) 
            / (o.getSigma() * sqrt(o.getT()));
}

long double BlackSholes::d2(const Option& o) {
    return d1(o) - (o.getSigma() * sqrt(o.getT()));
}
        
long double BlackSholes::putPrice(const Option& o) {
    return o.getK() * exp(- o.getR() * o.getT()) * N(-d2(o)) - o.getS0() * N(-d1(o));
}

long double BlackSholes::callPrice(const Option& o) {
    return o.getS0() * N(d1(o)) - o.getK() * exp(-o.getR() * o.getT()) * N(d2(o));
}

long double BlackSholes::price(const Option& o) {
    if (o.getType() == typeoption::CALL) {
        return BlackSholes::callPrice(o);
    }
    return BlackSholes::putPrice(o);
}

long double BlackSholes::errorCP(const Option& o, long double C, long double P) {
    return abs((C - P) - (o.getS0() -  o.getK() * exp(-o.getR() * o.getT()) ));
}

