#include "ODESolver.h"

static int n, func;
static double h, yo, x0, xn, e;

static QList<double>* x = new QList<double>,
    *y = new QList<double>,
    *dy = new QList<double>,
    *y_correct = new QList<double>,
    *yp = new QList<double>;

static double function(double x, double y){
    switch (func){
    case 1:
        return x*x - x/4.0 + 8 - y/16.0;
    case 0:
        return y/5.0 + x/6.0 + 1/7.0;
    }
}

static void eller(int a, int b){
    for (int i = a; i < b; i++){
        y->append(y->at(i-1) + h * function(x0 + (i-1)*h, y->at(i-1)));
    }
}

static double adams(int i){
    return h/24.0 * (55*yp->at(i) - 59*yp->at(i-1) + 37*yp->at(i-2) - 9*yp->at(i-3));
}

static double adams_correct(int i){
    return h/24.0 * (9*yp->at(i) + 19*yp->at(i-1) - 5*yp->at(i-2) + yp->at(i-3));
}

static void restart(bool isFirstTime){
    if (isFirstTime){
        n = 20;
        h = (xn - x0)/n;
    }
    else{
        n *= 2;
        h /= 2.0;
    }
    dy->clear();
    y_correct->clear();
    y->clear();
    yp->clear();
    x->clear();

    y->append(yo);
    eller(1, 4);
    for(int i = 0; i < 4; i++){
        yp->append(function(x0 + (i)*h, y->at(i)));
    }

    for (int i = 4; i < n; i++){
        y->append(y->at(i-1) + adams(i-1));
        yp->append(function(x0 + (i)*h, y->at(i)));
        double y_correct = y->at(i-1) + adams_correct(i);
        if (fabs(y->last() - y_correct)/29 > e) restart(false);
        y->replace(i, y_correct);
        yp->replace(i, function(x0 + (i)*h, y->at(i)));
    }
}

QList<QPair<double, double>>* odeSolve(int _func, double _x0, double _xn, double _y0, double _e){
    func = _func; x0 = _x0; yo = _y0; xn = _xn; e = _e;
    restart(true);
    QList<QPair<double, double>>* list = new QList<QPair<double, double>>;
    for (int i = 0; i < n; i++){
        QPair<double, double> p;
        p.first = x0 + i*h;
        p.second = y->at(i);
        list->append(p);
    }
    return list;
}
