#include <stdio.h>
#include <math.h>
#include "pegasus.h"

double x, y, z;
double theta_1, theta_2, theta_3, theta_4, theta_5;

int main(void)
{
	pegasus p( 40, 150, 120, 0, 100);
	p.forward( 0.000000, -0.514801, 1.955622, -1.440821, 0.000000, &x, &y, &z);
	printf("x = %f, y = %f, z = %f\r\n", x, y, z);
	p.reverse(160, 0, 0, 1, 1.57, &theta_1, &theta_2, &theta_3, &theta_4, &theta_5);
	printf("%f, %f, %f, %f, %f\r\n", theta_1, theta_2, theta_3, theta_4, theta_5);

}

