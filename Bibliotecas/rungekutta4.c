#include <stdio.h>
#include <math.h>

double funcao (double x, double y){

	double f;

	f=<funcao>;

	return f;
}

double rungekutta (double k, double h, double x, double y, double(*f)(double,double)){
	int i;
	double ponto,dy,termo1,termo2,termo3,termo4;

//	FILE *pfile;
//	pfile=fopen("exemplo4.dat","w");

//	ponto=x+k*h;
	for(i=1;i<=k;i++){
		ponto=i*h;
		termo1=h*f(x,y);
		termo2=h*f(x+0.5*h,y+0.5*termo1);
		termo3=h*f(x+0.5*h,y+0.5*termo2);
		termo4=h*f(x+h,y+termo3);
		dy=y+(termo1+2*termo2+2*termo3+termo4)/6;
		y=dy;
		x=x+h;
		printf("%lf		%lf \n",ponto,dy);
//		fprintf(pfile,"%2.3lf		%lf \n",ponto,dy);
	}

//	printf("%2.3lf		%lf \n",ponto,dy);
//	fprintf("%2.3lf		%lf \n",ponto,dy);

//	fclose(pfile);

	return 0;
}

int main(){
	double y,x,h,ponto;
	int k;

	printf("h: ");
	scanf("%lf",&h);
	printf("K: ");
	scanf("%d",&k);
	printf("Condição inicial X: ");
	scanf("%lf",&x);
	printf("Condição inicial Y: ");
	scanf("%lf",&y);

	rungekutta(k,h,x,y,funcao);

	return 0;
}
