#ifndef COMPMATH_LINEARSYSTEMSOLVER_H
#define COMPMATH_LINEARSYSTEMSOLVER_H
#include <math.h>

bool validateSystem(long double **A, long double *B, int n);
bool compute(long double **A, long double *B, int n, double e);
bool isDone(int n, double e);
long double * getAnswer();
long double * getPrecisions();
int getIterationsNumber();
#endif //COMPMATH_LINEARSYSTEMSOLVER_H
