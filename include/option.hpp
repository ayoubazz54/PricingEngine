#ifndef OPTION_HPP
#define OPTION_HPP


enum class typeoption {
    CALL, 
    PUT
};

struct parameters {
    long double S0;
    long double K;
    long double T;
    long double r;
    long double sigma;
};

typedef struct parameters parameters;

class Option {
    private:
        parameters par;
        typeoption type;
    public:
        Option(parameters par, typeoption type);
        ~Option();
        long double getS0() const;
        long double getK() const;
        long double getT() const;
        long double getR() const;
        long double getSigma() const;
        typeoption getType() const;
        
};


#endif