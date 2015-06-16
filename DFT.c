#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    double Re;
    double Im;
} Complex;

#define N 10
#define Fs 100

int main(int argc, char *argv[]){
    Complex *W = (Complex *)malloc(sizeof(Complex) * N);
    Complex *X = (Complex *)malloc(sizeof(Complex) * N);
    double *s = (double *)malloc(sizeof(double) * N);

    int k, n;
    for(k=0;k<N;k++){
        W[k].Re = 0.0;
        W[k].Im = 0.0;
        X[k].Re = 0.0;
        X[k].Im = 0.0;
        s[k] = 0.0;
    }

    double Ts = (double)1/(double)Fs;
    for(n=0;n<N;n++){
        s[n] = 8*sin(2.0*M_PI*10.0*n*Ts) + 4*cos(2.0*M_PI*20.0*n*Ts);
        //s[n] = cos(2*M_PI*n*Ts);
    }

    for(k=0;k<N;k++){
        W[k].Re = cos(2.0*M_PI*(double)k/N);
        W[k].Im = sin(-2.0*M_PI*(double)k/N);   
    }
    for(k=0;k<N;k++){
        for(n=0;n<N;n++){
            X[k].Re += s[n] * W[(k*n)%N].Re;
            X[k].Im += s[n] * W[(k*n)%N].Im;
        }
        X[k].Re /= N;
        X[k].Im /= N;
    }
    
    for(k=0;k<N;k++){
        printf("%d %lf %lf %lf\n", k, s[k], X[k].Re, X[k].Im);
    }

    free(W);
    free(X);
    free(s);
}
