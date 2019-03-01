#include <stdio.h>
#include <math.h>
#include <time.h>
#include "rungekutta.h"
#include "passovar.h"

double funcao (double x, double y){

	double f;

	f = 0.04*y;

	return f;
}

int main(){

	int i,j,k;
	double h,x,y,aux;
	double vx[4],vy[4];

	h = 0.2;
	k=2;

	vx[0] = 0;
	x = vx[0];
	vy[0] = 1000;
	y = vy[0];

	for(i=1;i<=3;i++){
		vy[i]=rungekutta(h,x,y,funcao);
		y=vy[i];
		x=x+h;
		vx[i]=x;
	}

	for(i=0;i<=k;i++){
		aux = passovar(h,vx,vy,funcao);
		printf(" %2.4lf \n",aux);
		for(j=0;j<=3;j++){
  			if(j==3){
  				vy[j]=aux;
  				vx[j]=x+h;
			}
  			else{
  				vy[j]=vy[j+1];
  				vx[j]=vx[j+1];
			}
		}
	}

	return 0;
}
