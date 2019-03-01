#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rungekutta.h"
#include "explicito.h"
#include "implicito.h"
#define R0 (double)6.96*pow(10,10)		// [R0]=cm
#define M0 (double)1.99*pow(10,33)		// [M0]=g
#define R (double)8.31*pow(10,7)		// [R]=erg/mol.K
#define G (double)6.673*pow(10,-8)		// [G]=dyn.cm²/g

double velocidade (double r, double v, double a, double M){

	return v * (2*pow(a,2)/r - G*M/pow(r,2))/(pow(v,2)-pow(a,2));
}

double passovariavel (double h, double e, double x, double y, double(*f)(double,double,double,double)){

	int i,j,k,l,N;
	double aux1,aux2,aux3,aux4;
	double vx[4],vy[4];

	vx[0] = x;
	vy[0] = y;

	for(i=1;i<=3;i++){
		vy[i]=rungekutta(h,x,y,velocidade);
		y=vy[i];
		x=x+h;
		vx[i]=x;
	}
	aux1 = explicito(h,vx,vy,velocidade);
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
		aux2 = implicito(h,vx,vy,velocidade);
		aux3 = fabs((aux2-aux1)/aux2);
		if(aux3<=e){
			printf(
			break;
		}
		aux1=aux2;
		vy[3]=aux1;
	}
	for(j=0;j<=3;j++){
		if(j==3){
			vy[j]=aux2;
			vx[j]=x+h;
			x=vx[j];
		}
		else{
			vy[j]=vy[j+1];
			vx[j]=vx[j+1];
		}
	}

	return aux2;
}

void main(){
	
	clock_t start, finish;
	start = clock();

	int i,j,k;
	double h,r,v,a,M,rstar,T,mi,rc,v0,v1,d0,d,vento,vento2,e;
	double aux,aux1,aux2,aux3,aux4,aux5,aux6,aux7,aux8;

	h = pow(10,6);
	k = 1.7*pow(10,6);
	M = M0;
	rstar = R0;
	rc = 5 * rstar;
	a = sqrt(G*M/(2*rc));
	mi = 0.602;
	T = pow(10,6);
	r = rstar;
	d0 = pow(10,-14);
	d=d0;
	e=pow(10,-5);
	v0 = a * pow(rc/rstar,2) * exp(1.5-2*rc/rstar);

	vento=passovariavel(h,k,e,r,v0,rc,a,M,funcao);


	v0=3.6247*a;
	r = rstar;
	vento2=passovariavel(h,k,e,r,v0,rc,a,M,funcao);

	system("gnuplot velocidade.gnu");

	finish = clock();
	printf("\n Tempo: %2.2lf segundos \n\n",(double)(finish - start)/CLOCKS_PER_SEC);
}
