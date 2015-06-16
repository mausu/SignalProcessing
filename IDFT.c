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
    Complex *s = (Complex *)malloc(sizeof(Complex) * N);

    int k, n;
    for(k=0;k<N;k++){
        W[k].Re = 0.0;
        W[k].Im = 0.0;
        X[k].Re = 0.0;
        X[k].Im = 0.0;
        s[k].Re = 0.0;
        s[k].Im = 0.0;
    }

    FILE *fp;
    fp = fopen("spectrum.txt", "r");
    if(fp == NULL){
        return -1;
    }
    double re, im;
    while(fscanf(fp, "%d %*lf %lf %lf\n", &k, &re, &im) != EOF){
        X[n].Re = re;
        X[n].Im = im;
        n++;
    }
    fclose(fp);

    double Ts = (double)1/(double)Fs;

    for(n=0;n<N;n++){
        W[n].Re = cos(2.0*M_PI*(double)n/N);
        W[n].Im = sin(2.0*M_PI*(double)n/N);   
    }
    for(n=0;n<N;n++){
        for(k=0;k<N;k++){
            s[n].Re += X[k].Re * W[(k*n)%N].Re-X[k].Im*W[(k*n)%N].Im;
            s[n].Im += X[k].Im * W[(k*n)%N].Re+X[k].Re*W[(k*n)%N].Im;
        }
        //s[n].Re = sqrt(s[n].Re*s[n].Re+s[n].Im*s[n].Im);
    }
    
    for(k=0;k<N;k++){
        printf("%d %lf %lf %lf %lf\n", k, s[k].Re, s[k].Im, X[k].Re, X[k].Im);
    }

    free(W);
    free(X);
    free(s);
}
