#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define Nmax 10
#define R0 (double)6.96*pow(10,10)		// [R0]=cm
#define M0 (double)1.99*pow(10,33)		// [M0]=g
#define R (double)8.31*pow(10,7)		// [R]=erg/mol.K
#define G (double)6.673*pow(10,-8)		// [G]=dyn.cm²/g

double funcao (double r, double v, double a, double M){
	return v * (2*pow(a,2)/r - G*M/pow(r,2))/(pow(v,2)-pow(a,2));
}

double LE (double v, double a){
	return v * exp(-0.5*pow(v/a,2));
}

double LD (double r, double rc, double v, double a){
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

double rungekutta (double h, double x, double y, double a, double M, double(*f)(double,double,double,double)){
	
	double dy,termo1,termo2,termo3,termo4;

	termo1=h*f(x,y,a,M);
	termo2=h*f(x+0.5*h,y+0.5*termo1,a,M);
	termo3=h*f(x+0.5*h,y+0.5*termo2,a,M);
	termo4=h*f(x+h,y+termo3,a,M);
	dy=y+(termo1+2*termo2+2*termo3+termo4)/6;

	return dy;
}

double implicito (double h, double *x, double *y, double a, double M, double(*f)(double,double,double,double)){

	double y1,termo0,termo1,termo2,termo3;
	
	termo0 = f(x[0],y[0],a,M);
	termo1 = f(x[1],y[1],a,M);
	termo2 = f(x[2],y[2],a,M);
	termo3 = f(x[3],y[3],a,M);
	y1 = y[2] + (h/24) * ( 9*termo3 + 19*termo2 - 5*termo1 - termo0 );

	return y1;

}

double explicito (double h, double *x, double *y, double a, double M, double(*f)(double,double,double,double)){

	double y1,termo0,termo1,termo2,termo3;
	
	termo0 = f(x[0],y[0],a,M);
	termo1 = f(x[1],y[1],a,M);
	termo2 = f(x[2],y[2],a,M);
	termo3 = f(x[3],y[3],a,M);
	y1 = y[3] + (h/24) * ( 55*termo3 - 59*termo2 + 37*termo1 - 9*termo0 );

	return y1;
}

double passovariavel (double h, int k, double e, double x, double y, double rc, double a, double M, double mi, double T, double d0, double d, double(*f)(double,double,double,double)){

	FILE *file;
	file=fopen("arq16.dat","w");

	int i,j,l,N,w;
	double aux1,aux2,aux3,aux4,aux5,aux6,aux7,aux8,aux9,aux10,aux11;
	double vx[4],vy[4];
	double v0 =y;
	vx[0] = x;
	vy[0] = y;

	for(w=0;w<=k;w++){
		for(i=1;i<=3;i++){
			vy[i]=rungekutta(h,x,y,a,M,funcao);
			y=vy[i];
			x=x+h;
			vx[i]=x;
		}
		aux1 = explicito(h,vx,vy,a,M,funcao);
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
			aux2 = implicito(h,vx,vy,a,M,funcao);
			aux3 = fabs((aux2-aux1)/aux2);
			if(aux3<=e){
				if(aux2/a>=0 && aux2/a<=4 && vx[3]/rc>=0 && vx[3]/rc<=1){
//					fprintf(file," %2.8lf	%2.8lf \n",vx[3]/rc,aux2/a);
					aux4=LE(aux2,a);
					aux5=LD(vx[3],rc,aux2,a);
					aux6=LE(a,a);
					aux7=LD(rc,rc,a,a);
//					fprintf(file," %lf	%lf \n",vx[3]/rc,aux4-aux5);
					aux8=energia(vx[3],aux2,M,T,mi);
					aux9=energia(rc,a,M,T,mi);
//					fprintf(file," %lf	%lf \n",vx[3]/rc,aux8/aux9);
					aux10=densidade(vx[3],R0,a,M,d0);
					fprintf(file," %lf	%lf \n",log(vx[3]/R0)-46.051759,log(aux10/d0));
					aux11=densidade2(vx[3],R0,a,v0,M,d0,d);
					d=aux11;
//					fprintf(file," %lf	%lf \n",log(vx[3]/R0)-46.051759,log(d/d0));
				}
				break;
			}
			aux1=aux2;
			vy[3]=aux1;
		}
		for(j=0;j<=3;j++){
			if(j==3){
				vy[j]=aux2;
				vx[j]=x+h;
				w=vx[j];
				if(vx[j]/rc==5)break;
			}
			else{
				vy[j]=vy[j+1];
				vx[j]=vx[j+1];
			}
		}
	}
	fclose(file);
	return aux2;
}

int main(){

	clock_t start, finish;
	start = clock();

	int i,j,k;
	double h,r,v,a,M,rstar,T,mi,rc,v0,v1,d0,d,vento,e;
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

	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	v0=3.6247*a;
	r = rstar;
//	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	v0=0.99999*a;
	r = 2*rc;
//	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	v0=1.00001*a;
	r = 2*rc;
//	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	v0=2.5*a;
	r = rstar;
//	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	v0=0.113*a;
	r = rstar;
//	vento=passovariavel(h,k,e,r,v0,rc,a,M,mi,T,d0,d,funcao);

	finish = clock();
	printf("\n Tempo: %2.2lf segundos \n\n",(double)(finish - start)/CLOCKS_PER_SEC);

	return 0;
}
