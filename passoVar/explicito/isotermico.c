#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "rungekutta.h"
#include "passovar.h"
#define R0 (double)6.96*pow(10,10)		// [R0]=cm
#define M0 (double)1.99*pow(10,33)		// [M0]=g
#define R (double)8.31*pow(10,7)		// [R]=erg/mol.K
#define G (double)6.673*pow(10,-8)		// [G]=dyn.cm²/g

double velocidade (double r, double v, double a, double M){

	return v * (2*pow(a,2)/r - G*M/pow(r,2))/(pow(v,2)-pow(a,2));
}

double funcao1 (double v, double a){

	return v * exp(-0.5*pow(v/a,2));
}

double funcao2 (double r, double rc, double v, double a){

	return a * pow(rc/r,2) * exp(1.5-2*rc/r);
}

double energia (double r, double v, double M, double T, double mi){

	return 0.5*pow(v,2) - G*M/r + 2.5*R*T/mi;
}

double densidade (double r, double rstar, double a, double M, double d0){

	return d0*exp(-G*M*pow(a,-2)*(1/rstar-1/r));
}

double densidade2 (double r, double rstar, double a, double v0, double M, double d0, double d){

	double f,g;

	g = pow(rstar/r,2)*v0*d0/(a*d);

	f = d0 * exp(-G*M*pow(a,-2)*(1/rstar-1/r)) * exp(-0.5*pow(g,2));

	return f;
}

int main(){

	clock_t start, finish;
	start = clock();

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

	FILE *parquivo;
	parquivo=fopen("arq6.dat","w");

	int i,j,k;
	double x[4],y[4];
	double h,r,v,a,M,rstar,T,mi,rc,v0,v1,d0,d;
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

	x[0]=r;
	v0 = a * pow(rc/rstar,2) * exp(1.5-2*rc/rstar);
	v=v0;
	y[0]=v0;

		for(i=1;i<=3;i++){
			y[i]=rungekutta(h,r,v,a,M,velocidade);
			v=y[i];
			r=r+h;
			x[i]=r;
		}
		for(i=0;i<=k;i++){
			aux = passovar(h,x,y,a,M,velocidade);
			if(aux/a>=0 && aux/a<=4 && x[3]/rc>=0 && x[3]/rc<=1){
//				fprintf(file," %2.8lf	%2.8lf \n",x[3]/rc,aux/a);
				fprintf(parquivo," %2.8lf	%2.8lf \n",log(x[3]/rstar),log(aux/a));
				aux1=funcao1(aux,a);
				aux2=funcao2(x[3],rc,aux,a);
				aux3=funcao1(a,a);
				aux4=funcao2(rc,rc,a,a);
				fprintf(pfile," %lf	%lf \n",x[3]/rc,aux1/aux3-aux2/aux4);
//				fprintf(pfile," %lf	%lf \n",x[3]/rc,aux1-aux2);
				aux5=energia(x[3],aux,M,T,mi);
				aux6=energia(rc,a,M,T,mi);
//				fprintf(arq," %lf	%lf \n",x[3]/rc,aux5/aux6);
				aux7=densidade(x[3],rstar,a,M,d0);
//				fprintf(arquivo," %lf	%lf \n",log(x[3]/rstar),log(aux7/d0));
				aux8=densidade2(x[3],rstar,a,v0,M,d0,d);
				d=aux8;
//				fprintf(parq," %lf	%lf \n",log(x[3]/rstar),log(d/d0));
			}
			for(j=0;j<=3;j++){
  				if(j==3){
  					y[j]=aux;
  					x[j]=r+h;
					r=x[j];
				}
  				else{
  					y[j]=y[j+1];
  					x[j]=x[j+1];
				}
			}
		}

	r=rstar;
	x[0]=r;
	v1=3.6247*a;
	v=v1;
	y[0]=v1;

		for(i=1;i<=3;i++){
			y[i]=rungekutta(h,r,v,a,M,velocidade);
			v=y[i];
			r=r+h;
			x[i]=r;
		}
		for(i=0;i<=k;i++){
			aux = passovar(h,x,y,a,M,velocidade);
			if(v/a>=0 && v/a<=4 && r/rc>=1 && r/rc<=5){
//				fprintf(file," %2.8lf	%2.8lf \n",x[3]/rc,aux/a);
				fprintf(parquivo," %2.8lf	%2.8lf \n",log(x[3]/rstar),log(aux/a));
				aux1=funcao1(aux,a);
				aux2=funcao2(x[3],rc,aux,a);
				aux3=funcao1(a,a);
				aux4=funcao2(rc,rc,a,a);
				fprintf(pfile," %lf	%lf \n",x[3]/rc,aux1/aux3-aux2/aux4);
//				fprintf(pfile," %lf	%lf \n",x[3]/rc,aux1/aux3-aux2);
				aux5=energia(x[3],aux,M,T,mi);
				aux6=energia(rc,a,M,T,mi);
//				fprintf(arq," %lf	%lf \n",x[3]/rc,aux5/aux6);
				aux7=densidade(x[3],rstar,a,M,d0);
//				fprintf(arquivo," %lf	%lf \n",log(x[3]/rstar),log(aux7/d0));
				aux8=densidade2(x[3],rstar,a,v1,M,d0,d);
				d=aux8;
//				fprintf(parq," %lf	%lf \n",log(x[3]/rstar),log(d/d0));
			}
			for(j=0;j<=3;j++){
  				if(j==3){
  					y[j]=aux;
  					x[j]=r+h;
					r=x[j];
				}
  				else{
  					y[j]=y[j+1];
  					x[j]=x[j+1];
				}
			}
		}


	system("gnuplot script1.gnu");
	system("gnuplot script2.gnu");
	system("gnuplot script3.gnu");
	system("gnuplot script4.gnu");
	fclose(file);
	fclose(pfile);
	fclose(arq);
	fclose(arquivo);
	fclose(parq);
	fclose(parquivo);
	finish = clock();
	printf("\n Tempo: %2.2lf segundos \n\n",(double)(finish - start)/CLOCKS_PER_SEC);

	return 0;
}
