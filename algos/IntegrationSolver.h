//
// Created by tania on 19.10.18.
//

#ifndef COMPMATH_INTEGRATIONSOLVER_H
#define COMPMATH_INTEGRATIONSOLVER_H
#include<cmath>
#include "helpers/Function.h"

bool compute(double upper, double lower, double eps, double (Function::*)(double), Function &obj);
double getAnswIntegr();
double getPrecision();
int getPartsNumber();


#endif //COMPMATH_INTEGRATIONSOLVER_H
