#ifndef COMPMATH_INTEGRATIONSOLVER_H
#define COMPMATH_INTEGRATIONSOLVER_H
#include <ctime>
#include "helpers/Function.h"

bool compute(double upper, double lower, double eps, double (Function::*)(double), Function &funcObj);
double getAnswIntegr();
double getPrecision();
int getPartsNumber();


#endif //COMPMATH_INTEGRATIONSOLVER_H
