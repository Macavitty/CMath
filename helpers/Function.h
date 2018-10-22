//
// Created by tania on 20.10.18.
//

#ifndef COMPMATH_FUNCTION_H
#define COMPMATH_FUNCTION_H


class Function {
public:
    friend class IntegrationTab;
    friend class IntegrationSolver;
private:
    double function_1(double);
    double function_2(double);
    double function_3(double);
    double function_4(double);
};


#endif //COMPMATH_FUNCTION_H
