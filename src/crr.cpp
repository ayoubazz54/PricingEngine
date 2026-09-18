#include "../include/crr.hpp"
#include <cmath>
#include <vector>
#include <stdexcept>


long double CRR::putPrice(const Option& o, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of steps must be stricly positive.");
    }

    long double dt = o.getT() / n;
    long double u = exp(o.getSigma() * sqrt(dt));
    long double d = 1 / u;
    long double p = (exp(o.getR() * dt) - d) / (u - d);

    if (p <= 0.0L || p >= 1.0L) {
        throw std::runtime_error("Invalid risk-neutral probability");
    }

    long double discount = exp(-o.getR() * dt);

    std::vector<long double> pricesTree(n + 1);
    for (int i = 0; i < n + 1; i++) {
        pricesTree[i] = std::max(o.getK() - o.getS0() * pow(u, 2*i - n), 0.0L);
    }
    for (int i = n; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            // we can see that : u ** i * d ** (n - i) == u ** (2*i - n)
            pricesTree[j] = discount * (p * pricesTree[j+1] + (1 - p) * pricesTree[j] );
        }
    }
    return pricesTree[0];

}


long double CRR::callPrice(const Option& o, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of steps must be stricly positive.");
    }

    long double dt = o.getT() / n;
    long double u = exp(o.getSigma() * sqrt(dt));
    long double d = 1 / u;
    long double p = (exp(o.getR() * dt) - d) / (u - d);

    if (p <= 0.0L || p >= 1.0L) {
        throw std::runtime_error("Invalid risk-neutral probability");
    }

    long double discount = exp(-o.getR() * dt);

    std::vector<long double> pricesTree(n + 1);
    for (int i = 0; i < n + 1; i++) {
        // we can see that : u ** i * d ** (n - i) == u ** (2*i - n)
        pricesTree[i] = std::max(o.getS0() * pow(u, 2*i - n) - o.getK(), 0.0L);
    }
    for (int i = n; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            pricesTree[j] = discount * (p * pricesTree[j+1] + (1 - p) * pricesTree[j] );
        }
    }
    return pricesTree[0];

}

long double CRR::price(const Option& o, int n) {
    if (o.getType() == typeoption::CALL) {
        return CRR::callPrice(o, n);
    }
    return CRR::putPrice(o, n);
}
