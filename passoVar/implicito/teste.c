#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rungekutta.h"
#include "explicito.h"
#include "implicito.h"
#define Nmax 1000

double funcao (double x, double y){

	return 0.04*y;
}

int main(){

	int i,j,k,l;
	double e,h,x,y,aux1,aux2,aux3,aux4;
	double vx[4],vy[4];

	e = pow(10,-4);
	h = 0.1;
	k=2;
	vx[0] = 1;
	x = vx[0];
	vy[0] = 1;
	y = vy[0];

	for(i=1;i<=3;i++){
		vy[i]=rungekutta(h,x,y,funcao);
		y=vy[i];
		x=x+h;
		vx[i]=x;
	}
	for(i=0;i<=k;i++){
		aux1 = explicito(h,vx,vy,funcao);
		for(j=0;j<=3;j++){
  			if(j==3){
  				vy[j]=aux1;
  				vx[j]=x+h;
			}
  			else{
  				vy[j]=vy[j+1];
  				vx[j]=vx[j+1];
			}
		}
		for(l=0;l<Nmax;l++){
			aux2 = implicito(h,vx,vy,funcao);
			aux3 = fabs((aux2-aux1)/aux2);
			if(aux3<=e){
				printf(" %2.5lf	%2.5lf \n",aux1,aux2);
				break;
			}
			aux1=aux2;
			vy[3]=aux1;
		}
		for(j=0;j<=3;j++){
  			if(j==3){
  				vy[j]=aux2;
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
