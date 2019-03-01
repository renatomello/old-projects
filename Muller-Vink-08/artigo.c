#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define R0 (double)6.96*pow(10,8)		// [R0] = m
#define M0 (double)1.99*pow(10,30)		// [M0] = kg
#define R (double)8.31				// [R] = J/mol.K
#define G (double)6.673*pow(10,-11)		// [G] = m³/kg.s²

double radacc (double r, double r0, double g0, double delta, double gama){

	double glinerad = g0 * pow((1-r0*pow(r,-delta)),gama) / pow(r,(1+delta));

	return glinerad;
}

double xarg (double r, double r0, double g0, double delta, double gama, double vcrit2){

	double rc = 1.011;
	double a = 2*vcrit2*(1/r-1/rc);
	double b = 2*g0/(r0*delta*(1+gama));
	double c = pow((1-r0/pow(r,delta)),(1+gama)) - pow((1-r0/pow(rc,delta)),(1+gama));

	double x = -pow(rc/r,4) * exp(-a-b*c-1);

	return x;
}

double vaprox (double r, double r0, double g0, double delta, double gama, double vcrit2){

	double a = vcrit2*(r0/r-pow(r0,(1-1/delta)));
	double b = g0*pow((1-r0/pow(r,delta)),(1+gama))/(delta*(1+gama));
	double v = sqrt((2/r0)*(a+b));

	return v;
}

double betalaw (double r, double r0line, double vinf, double beta){

	double v = vinf*pow((1-r0line/r),beta);

	return v;
}

int main(){

	FILE *file;
	file = fopen("gline.dat","w");

	FILE *file1;
	file1 = fopen("xarg.dat","w");

	FILE *file2;
	file2 = fopen("va.dat","w");

	FILE *file3;
	file3 = fopen("vbeta.dat","w");

	int i;
	double h = pow(10,-3);
	double k = pow(10,5);
	double Teff = 4.*pow(10,4);			//[Teff] = K
	double tal = 0.214;
	double M = 40.*M0;				//[M] = kg
	double mi = 0.602;
	double vinf = 323200;				//[vinf] = m/s
	double a = vinf/177.9;				//sqrt(R*Teff/mi);
	double beta = 0.7379;
	double r0line = 1.0095;
	double g0 = 17661;
	double r0 = 1.0016;
	double gama = 0.4758;
	double delta = 0.6878;
	double rstar = 11757*R0;

	double r = rstar;
	double rline = r / rstar;
	double vcrit2 = G*M*(1-tal)/(rstar*pow(a,2));

	for(i=0;i<=k;i++){
		double gline = radacc(rline,r0,g0,delta,gama);
		fprintf(file," %2.5lf	%2.5lf \n",rline,gline);

		double x = xarg(rline,r0,g0,delta,gama,vcrit2);
		fprintf(file1," %2.5lf	%2.5lf \n",rline,x);

		double v = vaprox(rline,r0,g0,delta,gama,vcrit2);
		fprintf(file2," %2.5lf	%2.5lf \n",rline,v);

		double vbeta = betalaw(rline,r0line,vinf,beta);
		fprintf(file3," %2.5lf	%2.5lf \n",rline,vbeta);
		
		rline+=h;
	}

	fclose(file);
	fclose(file1);
	fclose(file2);
	fclose(file3);

	return 0;
}
