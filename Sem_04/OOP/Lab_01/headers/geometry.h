#ifndef GEOMETRY
#define GEOMETRY

#include "error.h"
#include "dot.h"
#include "link.h"

typedef struct MODEL_TYPE {
	dots_t dots;
	link_t links;
	
} model_t;

void set_model_dots(model_t* mod, dots_t value);
void set_model_links(model_t* mod, link_t value);

dots_t* get_dots(model_t* mod);
link_t* get_links(model_t* mod);

typedef struct {
	double moveOX;
	double moveOY;
	double scale;
	double angleOX;
	double angleOY;
} change_t;

enum change_const { moveOX, moveOY, scale, angleOX, angleOY };

void set_change_t(change_t* change, change_const choose, double value);
double get_change_t(change_const choose, change_t change);
void Zero_change(change_t* change);

dots_t init_dots();
link_t init_links();
model_t init_model();

errs_num Dots_Change(dots_t* dots, change_t* change);

void RotateX(dot_t dot, double Alpha, dot_t centre);
void RotateY(dot_t dot, double Alpha, dot_t centre);

void Scale(dot_t dot, double Scale, dot_t centre);

void MoveOX(dot_t dot, double Move);
void MoveOY(dot_t dot, double Move);

void Init_center_model(dots_t* dots);

double get_max(dots_t dots, coord_const coord_name);
double get_min(dots_t dots, coord_const coord_name);

void Change_all_dots(dots_t* dots, change_t ch);
void Change_centre(dots_t* dots, change_t ch);
void recalculate_dot(dot_t* dot, dots_t dots, change_t ch);

#endif // GEOMETRY

