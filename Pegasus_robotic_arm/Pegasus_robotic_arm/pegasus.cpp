#include "pegasus.h"
#include <stdio.h>
#include <math.h>

pegasus::pegasus(double _link_1, double _link_2, double _link_3, double _link_4, double _link_5)
{
	link_1 = _link_1;
	link_2 = _link_2;
	link_3 = _link_3;
	link_4 = _link_4;
	link_5 = _link_5;

}

int pegasus::forward(double theta_1, double theta_2, double theta_3, double theta_4, double theta_5, double* x, double* y, double* z)
{
	//the forward is offset by by 90 degree
	*x = cos(theta_1) * ((link_2 * cos(theta_2)) + (link_3 * cos(theta_2 + theta_3)) + (link_5 * sin(theta_2 + theta_3 + theta_4)));
	*y = sin(theta_1) * ((link_2 * sin(theta_2)) + (link_3 * cos(theta_2 + theta_3)) + (link_2 * cos(theta_2 + theta_3 + theta_4)));
	*z = link_1 - (link_2 * sin(theta_2)) - (link_3 * sin(theta_2 + theta_3)) - (link_5 * cos(theta_2 + theta_3 + theta_4));
	return 1;
}

int pegasus::reverse(double x, double y, double z, double pitch, double yaw, double* theta_1, double* theta_2, double* theta_3, double* theta_4, double* theta_5)
{

	//fix to avoid devision by zero error
	if (pitch == 0)
	{
		pitch = 0.00000001;
	}

	double _theta_1 = atan(y / x);
	double c_1 = cos(_theta_1);
	double s_1 = sin(_theta_1);

	//intermediate break
	double b_2 = link_1 - (link_5 * cos(pitch)) - z;
	double b_1 = c_1 * x + s_1 * y + link_5 * sin(pitch);

	//claculations for theta 3
	double c_3 = ((b_1 * b_1) + (b_2 * b_2) - (link_2 * link_2) - (link_3 * link_3)) / (2 * link_2 * link_3);
	double _theta_3 = acos(c_3);
	double s_3 = sin(_theta_3);

	//calculations for theta 2
	double c_2 = (((link_2 + link_3 * c_3) * b_1) + ((link_3 * s_3) * b_2)) / ((link_2 * link_2) + (link_3 * link_3) + (2 * link_2 * link_3 * c_3));
	double _theta_2 = -acos(c_2);

	//calculations for theta_4
	double _theta_4 = pitch - _theta_2 - _theta_3;//this is where we handle the pitch from
	printf("Theta 4 = %f\r\n", _theta_4);


	//calculations for theta_5
	double R_31 = -(cos(yaw) * sin(_theta_2 + _theta_3 + _theta_4));
	double R_32 = (sin(_theta_2 + _theta_3 + _theta_4) * sin(yaw));

	printf("R-31 is %f\r\n", R_31);
	printf("R-32 IS %f\r\n", R_32);

	//double R_31 = 0.233;
	//double R_32 = 0.3536;

	double _theta_5 = atan(((R_32) / (-(R_31))));//this is where we handle the roll from

	//fixing the points
	*theta_1 = _theta_1;
	*theta_2 = _theta_2;
	*theta_3 = _theta_3;
	*theta_4 = _theta_4;
	*theta_5 = _theta_5;


	return 1;
}

