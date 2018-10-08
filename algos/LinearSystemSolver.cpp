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
long double *Xnext, // (k+1)th  approximation
        *Xcurrent, // kth approximation
        *P; // accuracies

bool compute(long double **A, long double *B, int n, double e) {
    Xnext = new long double[n];
    Xcurrent = new long double[n];
    if (validateSystem(A, B, n)) {
        // 0th approximation
        for (int i = 0; i < n; i++) {
            Xnext[i] = B[i] / A[i][i];
            Xcurrent[i] = 0;
        }
        k = 1;
        while (!isDone(n, e) && k < M) {
            // compute next approximations
            for (int i = 0; i < n; i++) {
                Xcurrent[i] = Xnext[i];
                Xnext[i] = B[i] / A[i][i];
            }
            for (int i = 0; i < n; i++) {
                for (auto j = 0; j < i; j++) {
                    Xnext[i] -= Xnext[j] * A[i][j] / A[i][i];
                }
                for (auto j = i + 1; j < n; j++) {
                    Xnext[i] -= Xcurrent[j] * A[i][j] / A[i][i];
                }
            }
            k++;
        }
        P = new long double[n];
        for (auto i = 0; i < n; i++) {
            P[i] = abs((double) (Xnext[i] - Xcurrent[i]));
        }
        return true;
    } else {
        // the system is not diagonally dominant;
        return false;
    }

}

bool isDone(int n, double e) {
    long double precision = 0;
    for (int i = 0; i < n; i++)
        precision = max(precision, abs(Xnext[i] - Xcurrent[i]));
    return e >= precision;
}

bool validateSystem(long double **A, long double *B, int n) {
    long double summ = 0;
    bool maxElem[n][n]; // this matrix indicates potential diagonal elements
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) maxElem[i][j] = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            summ += abs(A[i][j]);
        for (int j = 0; j < n; j++) {
            if (2 * abs(A[i][j]) >= summ && A[i][j] != 0) {
                maxElem[i][j] = true;
            }
        }
        summ = 0;
    }
    long double tmpA[n][n];
    long double tmpB[n];
    for (int i = 0; i < n; i++) { // for each row find right diagonal element
        bool is = false;
        for (int j = 0; j < n; j++) {
            if (maxElem[j][i]) {
                is = true;
                for (int l = 0; l < n; l++) {
                    tmpA[i][l] = A[j][l];
                }
                tmpB[i] = B[j];
                break;
            }
        }
        if (!is) return false;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            A[i][j] = tmpA[i][j];
        B[i] = tmpB[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
           cout << A[i][j] << " ";
        }
        cout << endl;
    }
    return true;
}

long double *getAnswer() {
    return Xnext;
}

long double *getPrecisions() {
    return P;
}

int getIterationsNumber() {
    return k;
}