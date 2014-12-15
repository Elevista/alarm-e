#include "integral.h"
double Power(double x)
{
	return pow(x,2);
}
double Root(double x)
{
	return sqrt(x);
}
void IntegrateRect(double (*f)(double), double a, double b, int n)
{
	int i;
	double h = ( b - a ) / (double)n;
	double result = 0.0;
	for ( i = 0; i < n; i++ )
		result += f(a+h/2.0+(double)i*h) * h;
	printf("Rectangle method   : %lf\n",  result);

}

void IntegrateTrapezoidal(double (*f)(double), double a, double b, int n)
{
	int i;
	double h = ( b - a ) / (double)n;
	double result = 0.0;
	for ( i = 0; i < n; i++ )
			result += ( f(a+(double)i*h) + f(a+((double)i+1.0)*h) ) * h/2.0;
	printf("Trapezoidal method : %lf\n",  result);

}
void IntegrateSimpson(double (*f)(double), double a, double b, int n, double tolerance)
{
	int i;
	double h = ( b - a ) / (double)n;
	double result = 0.0;
	for ( i = 0; i < n; i++ )
		result += ( f(a+(double)i*h) + 4*f(a+(double)i*h+h/2.0) + f(a+((double)i+1.0)*h) ) * h/6.0;
	printf("Simson's method    : %lf\n",  result);
}

