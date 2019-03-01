#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R0 (double)6.96*pow(10,8)		// [R0] = m
#define M0 (double)1.99*pow(10,30)		// [M0] = kg
#define R (double)8.31				// [R] = J/mol.K
#define G (double)6.673*pow(10,-11)		// [G] = m³/kg.s²

double vline (double r, double r0, double vcrit2, double g0, double delta, double gama, double B)
{
	double a = r0/r - pow(r0,(1-1/delta));
	double b = pow((1-r0/pow(r,delta)),(1+gama));
	double c = delta*(1+gama);
	double vast = sqrt(2*(vcrit2*a + g0*b/c)/r0);
	double v = vast/sqrt(1-B);

	return v;
}

double betalaw (double r, double r0line, double vinf, double beta, double B)
{
	double vast = vinf*pow((1-r0line/r),beta);
	double v = vast/sqrt(1-B);

	return v;
}

int main()
{
	FILE *file;
	file = fopen("B05.dat","w");

	FILE *file1;
	file1 = fopen("betaB05.dat","w");

	int i = 0;
	double h = 1.*pow(10,-3);
	double k = 1.*pow(10,5);
	double Teff = 4.*pow(10,4);			//[Teff] = K
	double tal = 0.214;
	double M = 40.*M0;				//[M] = kg
	double mi = 0.602;
	double vinf = 323200;
	double a = vinf/177.9;				//sqrt(R*Teff/mi);
	double beta = 0.7379;
	double r0line = 1.0095;
	double g0 = 17661;
	double r0 = 1.0016;
	double gama = 0.4758;
	double delta = 0.6878;
	double rstar = 11757*R0;
	double B = 0.5;

	double r = rstar;
	double rline = r / rstar;
	double vcrit2 = G*M*(1-tal)/(rstar*pow(a,2));

	for(i=0;i<=k;i++){
		double v = vline(rline,r0,vcrit2,g0,delta,gama,B);
		fprintf(file," %2.5lf	%2.5lf \n",rline,v);

		double vbeta = betalaw(r,r0line,vinf,beta,B);
		fprintf(file1," %2.5lf	%2.5lf \n",rline,vbeta);

		rline+=h;
	}

	fclose(file);
	fclose(file1);

//	system("gnuplot script.gnu");

	return 0;
}
