#ifndef OPTION_HPP
#define OPTION_HPP


enum class typeoption {
    CALL, 
    PUT
};

struct parameters {
    double S0;
    double K;
    double T;
    double r;
    double sigma;
};

typedef struct parameters parameters;

class Option {
    private:
        parameters par;
        typeoption type;
    public:
        Option(parameters par, typeoption type);
        ~Option();
        double getS0() const;
        double getK() const;
        double getT() const;
        double getR() const;
        double getSigma() const;
        typeoption getType() const;
        
};


#endif