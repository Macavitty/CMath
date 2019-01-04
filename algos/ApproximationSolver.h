
#ifndef COMPMATH_APPROXIMATIONSOLVER_H
#define COMPMATH_APPROXIMATIONSOLVER_H
#include <QList>
#include <QPair>
#include <QString>
#include <math.h>
#include "LinearSystemSolver.h"


using namespace std;

QList<double>* approximate(QList<QPair<double, double>> *dots, int func);

#endif //COMPMATH_APPROXIMATIONSOLVER_H
