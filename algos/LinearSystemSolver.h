#ifndef COMPMATH_LINEARSYSTEMSOLVER_H
#define COMPMATH_LINEARSYSTEMSOLVER_H
bool validateSystem(long double **A, long double *B, int n);
void compute(long double **A, long double *B, int n, double e);
bool isDone(long double *Xnext, long double * Xcurrent, int n, double e);
#endif //COMPMATH_LINEARSYSTEMSOLVER_H
