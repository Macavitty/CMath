
#ifndef COMPMATH_APPROXIMATIONSOLVER_H
#define COMPMATH_APPROXIMATIONSOLVER_H
#include <QList>
#include <QPair>
#include <QString>
#include <math.h>
#include <iostream>
#include "LinearSystemSolver.h"


using namespace std;

QList<double>* approximate(QList<QPair<double, double>> *dots, int func);
QList<QPair<double, double>>* getSerBefore();
QList<QPair<double, double>>* getSerAfter();
QList<double>* apprLinear(QList<QPair<double, double>> *dots);
QList<double>* apprLogarithm(QList<QPair<double, double>> *dots);
QList<double>* apprQuadr(QList<QPair<double, double>> *dots);
QList<double>* apprPower(QList<QPair<double, double>> *dots);
QList<double>* apprExp(QList<QPair<double, double>> *dots);
double det (double, double, double, double, double, double, double, double, double);

#endif //COMPMATH_APPROXIMATIONSOLVER_H
