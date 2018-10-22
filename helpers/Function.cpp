//
// Created by tania on 20.10.18.
//

#include "Function.h"

// right now this class is nothing more than a functions container

typedef double (Function::*somefunc(double));

double Function::function_1 (double x){
    return x + x*x;
}
double Function::function_2 (double x){
    return x*2;
}
double Function::function_3 (double x){
    return x+x;
}
double Function::function_4 (double x){
    return x*x;
}
