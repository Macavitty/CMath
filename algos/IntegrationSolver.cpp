//
// Created by tania on 19.10.18.
//

#include <iostream>
#include "IntegrationSolver.h"

using namespace std;

int n; // as the number of partitions is unknown, we can take any (5 in our case)
double h; // step
double In, I;
const int M = 10000000; // max number of partitions

bool compute(double upper, double lower, double eps,
             double (Function::* func)(double), Function &obj) {
    In = 1, I = 0;
    for (n = 5; (n < M && fabs(In - I) / 3 >= eps); n *= 2) { // Runge method for approximation

        h = (upper - lower) / n; // new step

        double summ = (obj.*func)(upper) / 2 + (obj.*func)(lower) / 2;
        for (int i = 1; i < n; i++) {
            summ += (obj.*func)(lower + i * h);
        }
        if (isnan(summ)) return false;
        summ *= h;

        I = In;
        In = summ;
    }
    return true;
}

double getAnswIntegr() { return In; }

double getPrecision() { return fabs(In - I) / 3; }

int getPartsNumber() { return n; }
