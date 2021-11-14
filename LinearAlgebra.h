#pragma once
#include <math.h>

#define G 9.81

struct Point
{
	double x = 0;
	double y = 0;
};

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
};