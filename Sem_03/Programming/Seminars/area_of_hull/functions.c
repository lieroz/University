#include "functions.h"

bool checkConvexity(FILE* f){
	type x1, y1;
	type x2, y2;
	type x3, y3;

	int numberOfPoints;
	fscanf(f, "%d", &numberOfPoints);

	if (numberOfPoints < 3){
		fprintf(stderr, "Number of points must be more than 2 in order to build polygon!!!");
		return false;
	}

	fscanf(f, "%lf%lf", &x1, &y1);

	type tmpX, tmpY;
	fscanf(f, "%lf%lf", &tmpX, &tmpY);

	type result = 0;
	for (int i = 0; i < numberOfPoints; ++i){
		x2 = tmpX - x1;
		y2 = tmpY - y1;

		fscanf(f, "%lf%lf", &x3, &y3);

		PDEBUG("x1, y1 : (%lf, %lf);\nx2, y2 : (%lf, %lf);\nx3, y3 : (%lf, %lf);\n\n", x1, y1, tmpX, tmpY, x3, y3);

		x1 = tmpX;
		y1 = tmpY;

		tmpX = x3;
		tmpY = y3;

		if (!i){
			result = x3 * y2 - y3 * x2 + x2 * y1 - y2 * x1;
		} else{
			type newResult = x3 * y2 - y3 * x2 + x2 * y1 - y2 * x1;
			if ((newResult > 0 && result < 0) || (newResult < 0 && result > 0))
				return false;
		}
	}

	return true;
}

type getArea(FILE* f, bool clockwise){
	type x1, y1;
	type x2, y2;
	type tmpX, tmpY;

	int numberOfPoints;
	fscanf(f, "%d", &numberOfPoints);
	fscanf(f, "%lf%lf", &x1, &y1);

	tmpX = x1;
	tmpY = y1;

	double area = 0;
	for (int i = 0; i < numberOfPoints; ++i){
		fscanf(f, "%lf%lf", &x2, &y2);

		if (i == numberOfPoints - 1){
			x2 = tmpX;
			y2 = tmpY;
		}

		double avgHeight = (y1 + y2) / 2;
		double width;

		if (clockwise)
			width = (x2 - x1);
		else
			width = (x1 - x2);

		double trapeziumArea = (avgHeight * width);
		PDEBUG("x1, y1 : (%lf, %lf);\nx2, y2 : (%lf, %lf);\nh = %lf;\nw = %lf;\nTrapeze area = %lf;\n\n", x1, y1, x2, y2, avgHeight, width, trapeziumArea);

		x1 = x2;
		y1 = y2;

		if (clockwise)
			area += trapeziumArea;
		else
			area -= trapeziumArea;
	}

	return area;
}