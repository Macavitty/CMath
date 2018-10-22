//
// Created by tania on 19.10.18.
//

#ifndef COMPMATH_INTEGRATIONSOLVER_H
#define COMPMATH_INTEGRATIONSOLVER_H
#include<cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers/Function.h"

bool compute(double upper, double lower, double eps, double (Function::*)(double), Function &obj);
double getAnswInt();
double getPrecision();
int partNumber();


#endif //COMPMATH_INTEGRATIONSOLVER_H
