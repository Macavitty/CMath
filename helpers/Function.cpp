//
// Created by tania on 20.10.18.
//

#include "Function.h"

// right now this class is nothing more than a functions container

double Function::function_0(double x) {
    return atan(copysign(pow((fabs(6 * x + 2)), 1.0 / 3), (6 * x + 2)));
}

double Function::function_1(double x) {
    return exp(2 * copysign(pow(fabs(x), 1.0 / 5), x) * sin(x / 4));
}

double Function::function_2(double x) {
    return sqrt(x * x - 5.0 / 6);
}

double Function::function_3(double x) {
    return log(3 + x * x) / (log(4) * 5}
