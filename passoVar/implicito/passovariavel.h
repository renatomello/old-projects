#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Nmax 10

double passovariavel (double h, double e, double x, double y, void(*g)(double x,double y, double *)){

	int i,j,k,l,N;
	double aux1,aux2,aux3,aux4;
	double vx[4],vy[4];

	N=1;
	size_t tamanho;
	tamanho=sizeof(double)*N;
	f=(double*)malloc(tamanho);

	g(x,y,f);
	vx[0] = x;
	vy[0] = y;

	for(i=1;i<=3;i++){
		vy[i]=rungekutta(h,x,y,f[0]);
		y=vy[i];
		x=x+h;
		vx[i]=x;
	}
	aux1 = explicito(h,vx,vy,f[0]);
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
		aux2 = implicito(h,vx,vy,f[0]);
		aux3 = fabs((aux2-aux1)/aux2);
		if(aux3<=e){
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

	return aux2;
}
