#pragma once
#include <math.h>

#define G 9.81
#define deg2rad 57.2957795

struct Point
{
	double x = 0;
	double y = 0;
};

double Distance2D(Point a, Point b);

//Linear function
struct Lfunc
{
	// y = ax + b
	double a = 0;
	double b = 0;

	double getValue(double x) {
		double y = (a * x) + b;
		return y;
	}

	void SetB(double x, double y) {
		b = y - (a * x);
	}
};

//Angled throw function
struct ATfunc
{
	double a = 0;
	double p = 0;

	double getValue(double x) {
		double y = x * tan(a) - ((G * pow(x, 2)) / (2 * pow(p, 2) * pow(cos(a), 2)));
		return y;
	}

	double getValueOffset(double x, Point offset) {
		//Notation for the Desmos.com/calculator
		//y\ -j=\ \left(x-i\right)\tan\left(a\right)-\frac{9.81\left(x-i\right)^{2}}{2p^{2}\cdot\cos^{2}a}

		double y = offset.y + (x - offset.x) * tan(a) - ((G * pow(x - offset.x, 2)) / (2 * pow(p, 2) * pow(cos(a), 2)));
		return y;
	}
};