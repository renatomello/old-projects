#include <stdio.h>
#include <math.h>

double funcao (double x, double y){

	double f;

	f=<funcao>;

	return f;
}

double rungekutta (int k, double h, double x, double y, double(*f)(double,double)){
	int i;
	double ponto,dy,funcao,termo1,termo2,termo3;

	ponto=x+k*h;
	for(i=1;i<=k;i++){
	//	ponto=i*h;
		termo1=h*f(x,y);
		termo2=h*f(x+0.5*h,y+0.5*termo1);
		termo3=h*f(x+3*h/4,y+3*termo2/4);
		dy=y+2*termo1/9+termo2/3+4*termo3/9;
		y=dy;
		x=x+h;
	//	printf("%d	%2.3lf	%lf \n",i,ponto,dy);
	}

	printf("%d	%lf	%lf \n",k,ponto,dy);

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
