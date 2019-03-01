#include <stdio.h>

double explicito (double h, double *x, double *y, double(*f)(double,double)){

	double y1,termo0,termo1,termo2,termo3;
	
	termo0 = f(x[0],y[0]);
	termo1 = f(x[1],y[1]);
	termo2 = f(x[2],y[2]);
	termo3 = f(x[3],y[3]);
	y1 = y[3] + (h/24) * ( 55*termo3 - 59*termo2 + 37*termo1 - 9*termo0 );

	return y1;
}
