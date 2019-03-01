#include <stdio.h>
#include <math.h>

double funcao(double x, double y){

	double f;

	f=<funcao>;

	return f;
}

double rungekutta (int k, double h, double x, double y, double(*f)(double,double)){
	int i;
	double ponto,dy,funcao;

	ponto=x+k*h;
	for(i=1;i<=k;i++){
		//ponto=i*k
		dy=y+0.5*h*(f(x,y)+f(x+h,y+h*f(x,y)));
		y=dy;
		x=x+h;
		//printf("%d	%2.3lf	%lf \n",i,ponto,dy);
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
