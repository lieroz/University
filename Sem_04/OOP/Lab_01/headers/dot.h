#ifndef DOT
#define DOT

#include <cstddef>

typedef struct DOT_TYPE {
	double X;
	double Y;
	double Z;
} dot_t;

enum coord_const { X_NAME, Y_NAME, Z_NAME };

double get_coord(dot_t dot, int i);
void set_coord(dot_t* dot, int i, double value);
void set_coord(dot_t* dot, double X, double Y, double Z);


typedef struct DOTS_TYPE {
	dot_t* dot;
	dot_t centre;
	size_t count;
} dots_t;

void set_arr_dot(dots_t* dots, dot_t* ptr);
void set_dot(dots_t* dots, int i, dot_t value);
void set_centre(dots_t* dots, dot_t value);
void set_count(dots_t* dots, size_t value);

void* get_arr_dot(dots_t dots);
dot_t get_dot(dots_t dots, size_t i);
size_t get_dots_count(dots_t dots);
dot_t get_dot_centre(dots_t dots);

int clear_arr_dot(dots_t* dots);

#endif // DOT

