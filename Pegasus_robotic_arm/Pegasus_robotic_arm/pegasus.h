#pragma once


class pegasus
{
private:

	double link_1, link_2, link_3, link_4, link_5;

public:
	pegasus(double _link_1, double _link_2, double _link_3, double _link_4, double _link_5);
	int forward(double theta_1, double theta_2, double theta_3, double theta_4, double theta_5, double* x, double* y, double* z);
	int reverse(double x, double y, double z, double pitch, double yaw, double* theta_1, double* theta_2, double* theta_3, double* theta_4, double* theta_5);
};
