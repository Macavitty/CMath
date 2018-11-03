//
// Created by tania on 19.10.18.
//

#include <iostream>
#include "IntegrationSolver.h"

using namespace std;

int n = 5; // as the number of partitions is unknown, we can take any (5 in our case)
double h; // step
double I2n, In;
const int M = 10000000; // max number of partitions

bool compute(double upper, double lower, double eps,
             double (Function::* func)(double), Function &obj) {

    h = (upper - lower);
    I2n = ((obj.*func)(upper) / 2 + (obj.*func)(lower) / 2)*h;
    if (isnan(I2n)) return false;
    In = 0;
    for ( ; (n < M && fabs(I2n - In) / 3 >= eps); n *= 2) { // Runge method for approximation

        double summ = I2n / h;
        h /= 2; // new step

        /*
         for example
         was:
            n = 4, h = 2
         new:
            n = 8, h = 1
         we already have computed:
            f(a + 0*2) = fa,
            f(a + 1*2),
            f(a + 2*2),
            f(a + 3*2),
            f(a + 4*2) = fb
         we are going to compute:
            f(a + 0*1) = fa,
            f(a + 1*1),
            f(a + 2*1), // done
            f(a + 3*1),
            f(a + 4*1), // done
            f(a + 5*1),
            f(a + 6*1), // done
            f(a + 7*1),
            f(a + 8*1) = fb

        next:
            f(a + 0*0.5) = fa,
            f(a + 1*0.5),
            f(a + 2*0.5), // done
            f(a + 3*0.5),
            f(a + 4*0.5), // done
            f(a + 5*0.5),
            f(a + 6*0.5), // done
            f(a + 7*0.5),
            f(a + 8*0.5),  // done
            f(a + 9*0.5),
            f(a + 10*0.5),  // done
            f(a + 11*0.5),
            f(a + 12*0.5),  // done
            f(a + 13*0.5),
            f(a + 14*0.5),  // done
            f(a + 15*0.5),
            f(a + 16*0.5) = fb
         so:
            for (int i = 1; i < n; i +=2) {...}
         */
        for (int i = 1; i < n; i += 2) {
            summ += (obj.*func)(lower + i * h);
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
