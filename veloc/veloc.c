#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "rungekutta4.h"
#define R0 (double)6.96*pow(10,10)		// [R0]=cm
#define M0 (double)1.99*pow(10,33)		// [M0]=g
#define R (double)8.31*pow(10,7)		// [R]=erg/mol.K
#define G (double)6.673*pow(10,-8)		// [G]=dyn.cm²/g

double funcao (double r, double v, double M, double a){

	double f;

	f = v * ( 2*pow(a,2)/r - G*M*pow(r,-2) ) / ( pow(v,2) - pow(a,2) ) ;

	return f;
}

double funcao1 (double v, double a){

	double f;

	f = v * exp(-0.5*pow(v/a,2));

	return f;
}

double funcao2 (double r, double rc, double v, double a){

	double f;

	f = a * pow(rc/r,2) * exp(1.5-2*rc/r);

	return f;
}

double energia (double r, double v, double M, double T, double mi){

	double f;

	f = 0.5*pow(v,2) - G*M/r + 2.5*R*T/mi;

	return f;
}

double densidade (double r, double rstar, double a, double M, double d0){

	double f;

	f = d0*exp(-G*M*pow(a,-2)*(1/rstar-1/r));

	return f;
}

double densidade2 (double r, double rstar, double a, double v0, double M, double d0, double d){

	double f,g;

	g = pow(rstar/r,2)*v0*d0/(a*d);

	f = d0 * exp(-G*M*pow(a,-2)*(1/rstar-1/r)) * exp(-0.5*pow(g,2));

	return f;
}

int main(){

	double i,k,h,r,v,a,M,rstar,T,mi,rc,v0,v1,d0,d;
	double aux,aux1,aux2,aux3,aux4,aux5,aux6,aux7,aux8;

	clock_t start, finish;
	start = clock();

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
	v0 = a * pow(rc/rstar,2) * exp(1.5-2*rc/rstar);
	v=v0;

	FILE *file;
	file=fopen("arq1.dat","w");

	FILE *pfile;
	pfile=fopen("arq2.dat","w");

	FILE *arq;
	arq=fopen("arq3.dat","w");

	FILE *arquivo;
	arquivo=fopen("arq4.dat","w");

	FILE *parq;
	parq=fopen("arq5.dat","w");

	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=1){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
			aux1=funcao1(v,a);
			aux2=funcao2(r,rc,v,a);
			aux3=funcao1(a,a);
			aux4=funcao2(rc,rc,a,a);
			fprintf(pfile," %lf	%lf \n",r/rc,aux1-aux2);
			aux5=energia(r,v,M,T,mi);
			aux6=energia(rc,a,M,T,mi);
			fprintf(arq," %lf	%lf \n",r/rc,aux5/aux6);
			aux7=densidade(r,rstar,a,M,d0);
			fprintf(arquivo," %lf	%lf \n",log(r/rstar),log(aux7/d0));
			aux8=densidade2(r,rstar,a,v0,M,d0,d);
			d=aux8;
			fprintf(parq," %lf	%lf \n",log(r/rstar),log(d/d0));
		}
	}

	v=3.6247*a;
	v1=v;
	r=rstar;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=1 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
			aux1=funcao1(v,a);
			aux2=funcao2(r,rc,v,a);
			aux3=funcao1(a,a);
			aux4=funcao2(rc,rc,a,a);
			fprintf(pfile," %lf	%lf \n",r/rc,aux1-aux2);
			aux5=energia(r,v,M,T,mi);
			aux6=energia(rc,a,M,T,mi);
			fprintf(arq," %lf	%lf \n",r/rc,aux5/aux6);
			aux7=densidade(r,rstar,a,M,d0);
			fprintf(arquivo," %lf	%lf \n",log(r/rstar),log(aux7/d0));
			aux8=densidade2(r,rstar,a,v1,M,d0,d);
			d=aux8;
			fprintf(parq," %lf	%lf \n",log(r/rstar),log(d/d0));
		}
	}

/*
	v=0.003*a;
	r=rstar;	
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}
	}

	v=4*a;
	r=rstar;	
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}
	}

	v=1.5*a;
	r=0.647*rc;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}
	}

	v=2.5*a;
	r=rstar;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=2.5 && r/rc>=0 && r/rc<=0.257){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}

	}

	v=0.113*a;
	r=rstar;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=2.5 && r/rc>=0 && r/rc<=0.257){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}

	}

	v=1.001*a;
	r=2*rc;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}
	}

	v=0.999*a;
	r=2*rc;
	for(i=0;i<k;i++){
		aux=rungekutta(h,r,v,M,a,funcao);
		v=aux;
		r=r+h;
		if(v/a>=0 && v/a<=4 && r/rc>=0 && r/rc<=5){
			fprintf(file," %2.7lf		%2.7lf \n",r/rc,v/a);
		}
	}
*/
	system("gnuplot script1.gnu");
	system("gnuplot script2.gnu");
	system("gnuplot script3.gnu");
	system("gnuplot script4.gnu");
	fclose(file);
	fclose(pfile);
	fclose(arq);
	fclose(arquivo);
	fclose(parq);
	finish = clock();
	printf("\n Tempo: %2.2lf segundos \n\n",(double)(finish - start)/CLOCKS_PER_SEC);
	return 0;
}
