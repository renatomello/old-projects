#include <stdio.h>

double passovar (double h, double *x, double *y, double a, double M, double(*f)(double,double,double,double)){

	int N=4;
	double y1,termo0,termo1,termo2,termo3;
	
	termo0 = f(x[0],y[0],a,M);
	termo1 = f(x[1],y[1],a,M);
	termo2 = f(x[2],y[2],a,M);
	termo3 = f(x[3],y[3],a,M);
	y1 = y[3] + (h/24) * ( 55*termo3 - 59*termo2 + 37*termo1 - 9*termo0 );

	return y1;
}
