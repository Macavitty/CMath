#include "ApproximationSolver.h"

QList<double>* approximate(QList<QPair<double, double>> *dots, int func){
    QString type;
    switch (func){
    case 1:
        return apprQuadr(dots);
    case 2:
        return apprPower(dots);
    case 3:
        return apprExp(dots);
    case 4:
        return apprLogarithm(dots);
    default:
        return apprLinear(dots);
    }
}

QList<double>* apprLinear(QList<QPair<double, double>> *dots){
    double SX = 0, SX2 = 0, SY = 0, SXY = 0, a, b;
    int n = dots->size();
    QList<double> *coeff = new QList<double>;

    for (auto i = 0; i < n; i++){
        double x = dots->at(i).first;
        double y = dots->at(i).second;
        SX += x;
        SY += y;
        SX2 += x*x;
        SXY += x*y;
    }
    double fraction = SX2*n - SX*SX;
    a = (SXY*n - SX*SY)/fraction;
    b = (SX2*SY - SX*SXY)/fraction;
    coeff->append(a);
    coeff->append(b);
    return coeff;
}

QList<double>* apprLogarithm(QList<QPair<double, double>> *dots){
    double SX = 0, SXX = 0, SY = 0, SXY = 0, a, b;
    int n = dots->size();
    QList<double> *coeff = new QList<double>;

    for (auto i = 0; i < n; i++){
        double x = dots->at(i).first;
        double y = dots->at(i).second;
        SX += log(x);
        SY += y;
        SXX += log(x)*log(x);
        SXY += log(x)*y;
    }
    double fraction = SXX*n - SX*SX;
    a = (SXY*n - SX*SY)/fraction;
    b = (SXX*SY - SX*SXY)/fraction;
    coeff->append(a);
    coeff->append(b);
    return coeff;
}

QList<double>* apprQuadr(QList<QPair<double, double>> *dots){
    double SX = 0, SXX = 0, SX3 = 0, SX4 = 0, SY = 0,
            SXY = 0, SXXY = 0, a, b, c;
    int n = dots->size();
    QList<double> *coeff = new QList<double>;
    for (auto i = 0; i < n; i++){
        double x = dots->at(i).first;
        double y = dots->at(i).second;
        SX += x;
        SXX += x*x;
        SX3 += x*x*x;
        SX4 += x*x*x*x;
        SY += y;
        SXY += x*y;
        SXXY += x*x*y;
    }
    /*
    | n     sx      sx2 | sy
    | sx    sxx     sx3 | sxy
    | sxx   sx3     sx4 | sxxy
    */
    double d = det(n, SX, SXX, SX, SXX, SX3, SXX, SX3, SX4);
    if (d != 0.0){
        double dc = det(SY, SX, SXX, SXY, SXX, SX3, SXXY, SX3, SX4);
        double db = det(n, SY, SXX, SX, SXY, SX3, SXX, SXXY, SX4);
        double da = det(n, SX, SY, SX, SXX, SXY, SXX, SX3, SXXY);
        a = da/d;
        b = db/d;
        c = dc/d;
    }
    else { // kramer
        auto **A = new double *[9], *B = new double[3];
        for (int i = 0; i < 3; i++) A[i] = new double[3];
        B[0] = SY; B[1] = SXY; B[2] = SXXY;
        A[0][0] = n; A[0][1] = SX; A[0][2] = SXX;
        A[1][0] = SX; A[1][1] = SXX; A[1][2] = SX3;
        A[2][0] = SXX; A[2][1] = SX3; A[2][2] = SX4;
        if (compute(A, B, 3, 0.0001)){
            auto X = getAnswSLAY();
            a = X[0];
            b = X[1];
            c = X[2];
        }
    }
    coeff->append(a);
    coeff->append(b);
    coeff->append(c);
    return coeff;
}

QList<double>* apprPower(QList<QPair<double, double>> *dots){ // степенная
    double SX = 0, SXX = 0, SY = 0, SXY = 0, a, b;
    int n = dots->size();
    QList<double> *coeff = new QList<double>;
    for (auto i = 0; i < n; i++){
        double x = dots->at(i).first;
        double y = dots->at(i).second;
        SX += log(x);
        SY += log(y);
        SXX += log(x)*log(x);
        SXY += log(x)*log(y);
    }
    double fraction = SXX*n - SX*SX;
    b = ((SXY*n - SX*SY)/fraction);
    a = exp((SXX*SY - SX*SXY)/fraction);
    coeff->append(a);
    coeff->append(b);
    return coeff;
}

QList<double>* apprExp(QList<QPair<double, double>> *dots){ // экспоненциальная
    double SX = 0, SXX = 0, SY = 0, SXY = 0, a, b;
    int n = dots->size();
    QList<double> *coeff = new QList<double>;

    for (auto i = 0; i < n; i++){
        double x = dots->at(i).first;
        double y = dots->at(i).second;
        SX += x;
        SY += log(y);
        SXX += x*x;
        SXY += x*log(y);
    }
    double fraction = SXX*n - SX*SX;
    a = exp((SXX*SY - SX*SXY)/fraction);
    b = (SXY*n - SX*SY)/fraction;
    coeff->append(a);
    coeff->append(b);
    return coeff;
}

double det (double a, double b, double c, double d, double e, double f, double g, double h, double i){
    return a*e*i + b*f*g + c*d*h - c*e*g - a*f*h - b*d*i;
}
