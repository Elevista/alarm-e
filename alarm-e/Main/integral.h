#ifndef INTEGRAL
#define INTEGRAL

#pragma warning(disable:4996) 
#define _USE_MATH_DEFINES //M_PI && M_E 를 사용하기 위해 정의.math.h 보다 먼저 작성 해야 함
#include <stdio.h>
#include <math.h>
typedef enum METHOD {RECTANGULAR, TRAPEZOIDAL, SIMPSON} METHOD;
void IntegrateRect(double (*f)(double), double a, double b,  unsigned int n);
void IntegrateTrapezoidal(double (*f)(double), double a, double b,unsigned  int n);
void IntegrateSimpson(double (*f)(double), double a, double b,unsigned  int n);
double Power(double x);
double Root(double x);

#endif