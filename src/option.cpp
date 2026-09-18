#include "../include/option.hpp"

Option::Option(parameters par, typeoption type) : par(par), type(type) {}

Option::~Option() {}

long double Option::getS0() const {
    return par.S0;
}

long double Option::getK() const {
    return par.K;
}

long double Option::getT() const {
    return par.T;
}

long double Option::getR() const {
    return par.r;
}

long double Option::getSigma() const {
    return par.sigma;
}

typeoption Option::getType() const {
    return type;
}