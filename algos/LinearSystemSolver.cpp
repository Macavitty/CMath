#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "LinearSystemSolver.h"

using namespace std;

/*
 * This -class solves (at least tries to) a linear system
 * by using the Gauss–Seidel method
 * */

const int M = 10000; // max number of iterations
int k; // number of iterations

void compute(long double **A, long double *B, int n, double e) {
    auto *Xnext = new long double[n], *Xcurrent = new long double[n];
    if (validateSystem(A, B, n)) {
        // 0th approximation
        for (int i = 0; i < n; i++) {
            Xnext[i] = *(B + i) / *(*(A + i) + i);
            Xcurrent[i] = 0;
        }
        k = 1;
        while (!isDone(Xnext, Xcurrent, n, e) && k < M) {
            k++;
            // next approximations
            for (int i = 0; i < n; i++) {
                Xcurrent[i] = Xnext[i];
                Xnext[i] = B[i] / A[i][i];
            }
            for (int i = 0; i < n; i++) {
                for (auto j = 0; j < i; j++)
                    Xnext[i] -= Xnext[j] * A[i][j] / A[i][i];
                for (auto j = i + 1; j < n; j++)
                    Xnext[i] -= Xcurrent[j] * A[i][j] / A[i][i];
            }
        }
        //return Xnext;
    }
    printf("The numver of iterations : %d\n", k);
    cout << "The answer : " << endl;
    for (auto i = 0; i < n; i++) {
        cout << "x" << i << " = ";
        printf("%.10g; ", (double) Xnext[i]);
        printf(" approximation: %.10g \n", abs((double) (Xnext[i] - Xcurrent[i])));
    }
}

bool isDone(long double *Xnext, long double *Xcurrent, int n, double e) {
    long double pres = 0;
    for (int i = 0; i < n; i++)
        pres = max(pres, abs(Xnext[i] - Xcurrent[i]));
    return e >= pres;
}

bool validateSystem(long double **A, long double *B, int n) {
    long double summ = 0, s = 0;
    bool maxElem[n][n]; // this matrix indicates potential diagonal elements
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) maxElem[i][j] = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            s += abs(A[i][j]);
        for (int j = 0; j < n; j++) {
            if (2 * abs(A[i][j]) > s && A[i][j] != 0) {
                maxElem[i][j] = true;
            }
        }
        s = 0;
    }
    long double tmpA[n][n];
    long double tmpB[n];
    for (int i = 0; i < n; i++) { // for each row find right diagonal element
        bool is = false;
        for (int j = 0; j < n; j++) {
            if (maxElem[j][i]) {
                is = true;
                *tmpA[i] = *A[j];
                tmpB[i] = B[j];
                break;
            }
        }
        if (!is) return false;
    }
    **A = **tmpA, *B = *tmpB;
    return true;
}