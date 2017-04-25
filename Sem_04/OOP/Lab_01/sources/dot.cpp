#include "dot.h"
#include "ptr.h"

double get_coord(dot_t dot, int i) {
	switch (i) {
		
		case X_NAME:
			return dot.X;
		
		case Y_NAME:
			return dot.Y;
		
		case Z_NAME:
			return dot.Z;
		
		default:
			return 0;
	}
}

void set_coord(dot_t* dot, int i, double value) {
	switch (i) {
		
		case X_NAME:
			dot->X = value;
			break;
			
		case Y_NAME:
			dot->Y = value;
			break;
			
		case Z_NAME:
			dot->Z = value;
			break;
			
		default:
			break;
	}
}

void set_coord(dot_t* dot, double X, double Y, double Z) {
	dot->X = X;
	dot->Y = Y;
	dot->Z = Z;
}

void set_arr_dot(dots_t* dots, dot_t* ptr) {
	dots->dot = ptr;
}

void set_dot(dots_t* dots, int i, dot_t value) {
	dots->dot[i] = value;
}

void set_centre(dots_t* dots, dot_t value) {
	dots->centre = value;
}

void set_count(dots_t* dots, size_t value) {
	dots->count = value;
}

void* get_arr_dot(dots_t dots) {
	return (void*) dots.dot;
}

dot_t get_dot(dots_t dots, size_t i) {
	return dots.dot[i];
}

size_t get_dots_count(dots_t dots) {
	return dots.count;
}

dot_t get_dot_centre(dots_t dots) {
	return dots.centre;
}

int clear_arr_dot(dots_t* dots) {
	Clear_Ptr((void*) (dots->dot));
	
	return 0;
}
