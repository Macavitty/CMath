//
// Created by tania on 19.10.18.
//

#include "IntegrationSolver.h"

using namespace std;

int n; // as the number of partitions is unknown, we can take any (5 in our case)
double h; // step
double In, I;


bool compute(double upper, double lower, double eps, double (Function::* func)(double), Function &obj){
    printf("HAH it works!\n");
    In = 1, I = 0;
    for (n = 5; (n < 100000 && fabs(In - I) > eps); n *= 2){

        h = (upper - lower)/n; // step

        double summ = (obj.*func)(upper)/2 + (obj.*func)(lower)/2;
        printf("%f\n", In);
        for (int i = 1; i < n; i++){
            summ += (obj.*func)(lower + i*h);
        }
        summ *= h;

        I = In;
        In  = summ;
    }

}

double getAnswInt(){
    return In;
}
double getPrecision(){
    return 1;
}
int partNumber(){
    return n;
}
