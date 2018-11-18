//
// Created by tania on 19.10.18.
//

#include <iostream>
#include "IntegrationSolver.h"

using namespace std;

int n; // as the number of partitions is unknown, we can take any (5 in our case)
double h; // step
double I2n, In;
const int M = 10000000; // max number of partitions

bool compute(double upper, double lower, double eps,
             double (Function::* func)(double), Function &funcObj) {
    n = 5;
    h = (upper - lower) / n;

    // find integrals for n0 and n0 * 2
    In = ((funcObj.*func)(upper) / 2 + (funcObj.*func)(lower) / 2);
    I2n = In;
    for (int i = 1; i < n; i++) In += (funcObj.*func)(lower + i * h);
    In *= h;
    n *= 2;
    h /= 2;
    for (int i = 1; i < n; i++) I2n += (funcObj.*func)(lower + i * h);
    I2n *= h;

    if (isnan(I2n)) return false;
    if (fabs(I2n - In) / 3 < eps) return true;

    // reaching the needed precision
    for (n *= 2; (n < M && fabs(I2n - In) / 3 >= eps); n *= 2) { // Runge method for approximation

        h /= 2; // new step

        double summ = (funcObj.*func)(upper) / 2 + (funcObj.*func)(lower) / 2;
        for (int i = 1; i < n; i++) {
            summ += (funcObj.*func)(lower + i * h);
        }
        if (isnan(summ)) return false;
        summ *= h;

        In = I2n;
        I2n = summ;
    }
    return true;
}

double getAnswIntegr() { return I2n; }

double getPrecision() { return fabs(I2n - In) / 3; }

int getPartsNumber() { return n; }
