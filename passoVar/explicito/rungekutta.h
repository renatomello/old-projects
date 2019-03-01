#include <stdio.h>
#include <math.h>

double rungekutta (double h, double x, double y, double a, double M, double(*f)(double,double,double,double)){
	
	double dy,termo1,termo2,termo3,termo4;

	termo1=h*f(x,y,a,M);
	termo2=h*f(x+0.5*h,y+0.5*termo1,a,M);
	termo3=h*f(x+0.5*h,y+0.5*termo2,a,M);
	termo4=h*f(x+h,y+termo3,a,M);
	dy=y+(termo1+2*termo2+2*termo3+termo4)/6;

	return dy;
}
