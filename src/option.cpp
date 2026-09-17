#include "../include/option.hpp"

Option::Option(parameters par, typeoption type) : par(par), type(type) {}

Option::~Option() {}

double Option::getS0() const {
    return par.S0;
}

double Option::getK() const {
    return par.K;
}

double Option::getT() const {
    return par.T;
}

double Option::getR() const {
    return par.r;
}

double Option::getSigma() const {
    return par.sigma;
}

typeoption Option::getType() const {
    return type;
}