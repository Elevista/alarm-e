#ifndef INTEGRAL
#define INTEGRAL

#pragma warning(disable:4996) 
#define _USE_MATH_DEFINES //M_PI && M_E �� ����ϱ� ���� ����.math.h ���� ���� �ۼ� �ؾ� ��
#include <stdio.h>
#include <math.h>
typedef enum METHOD {RECTANGULAR, TRAPEZOIDAL, SIMPSON} METHOD;
void IntegrateRect(double (*f)(double), double a, double b,  unsigned int n);
void IntegrateTrapezoidal(double (*f)(double), double a, double b,unsigned  int n);
void IntegrateSimpson(double (*f)(double), double a, double b,unsigned  int n);
double Power(double x);
double Root(double x);

#endif