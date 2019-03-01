#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double implicito (double h, double *x, double *y, double(*f)(double,double)){

	double y1,termo0,termo1,termo2,termo3;
	
	termo0 = f(x[0],y[0]);
	termo1 = f(x[1],y[1]);
	termo2 = f(x[2],y[2]);
	termo3 = f(x[3],y[3]);
	y1 = y[2] + (h/24) * ( 9*termo3 + 19*termo2 - 5*termo1 - termo0 );

	return y1;

}
