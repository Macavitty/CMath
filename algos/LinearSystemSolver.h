#ifndef COMPMATH_LINEARSYSTEMSOLVER_H
#define COMPMATH_LINEARSYSTEMSOLVER_H
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

bool validateSystem(double **A, double *B, int n);
bool compute(double **A, double *B, int n, double e);
bool isDone(int n, double e);
double * getAnswSLAY();
double * getPrecisions();
int getIterationsNumber();
#endif //COMPMATH_LINEARSYSTEMSOLVER_H
