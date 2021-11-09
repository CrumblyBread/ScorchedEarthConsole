#include "LinearAlgebra.h"

double Distance2D(Point a, Point b) {
	double d;
	
	d = sqrt(pow(a.x - b.x, 2) - pow(a.y - b.y, 2));

	return fabs(d);
}