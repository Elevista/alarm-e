#include "integral.h"

int main()
{
	printf("Integral of x \n");
	
	IntegrateRect(sin, 0, M_PI, 100); 
	IntegrateTrapezoidal(sin, 0, M_PI, 100); 
	IntegrateSimpson(sin, 0, M_PI, 100); 
	

	IntegrateRect(log, 1, M_E, 100);
	IntegrateTrapezoidal(log, 1, M_E, 100);
	IntegrateSimpson(log, 1, M_E, 100);
	
	IntegrateRect(Power, 0, 1, 100);
	IntegrateTrapezoidal(Power, 0, 1, 100);
	IntegrateSimpson(Power, 0, 1, 100);
	
	IntegrateRect(Root, 0, 1, 100);
	IntegrateTrapezoidal(Root, 0, 1, 100);
	IntegrateSimpson(Root, 0, 1, 100);
	
	return 0;
}

