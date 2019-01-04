#ifndef COMPMATH_ODESOLVER_H
#define COMPMATH_ODESOLVER_H

#include <QList>
#include <QPair>
#include <math.h>
#include <cmath>

QList<QPair<double, double>>*  odeSolve(int f, double x0, double xend, double y0, double e);

#endif //COMPMATH_ODESOLVER_H
