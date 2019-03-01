#include <stdio.h>
#include <math.h>

double rungekutta (double h, double x, double y, double M, double a, double(*f)(double,double,double,double)){
	
	double dy,termo1,termo2,termo3,termo4;

	termo1=h*f(x,y,M,a);
	termo2=h*f(x+0.5*h,y+0.5*termo1,M,a);
	termo3=h*f(x+0.5*h,y+0.5*termo2,M,a);
	termo4=h*f(x+h,y+termo3,M,a);
	dy=y+(termo1+2*termo2+2*termo3+termo4)/6;
	y=dy;

	return y;
}
