#include "geometry.h"

dots_t init_dots() {
	dots_t dots;
	dot_t centre;
	set_coord(&centre, X_NAME, 0);
	set_coord(&centre, Y_NAME, 0);
	set_coord(&centre, Z_NAME, 0);
	set_count(&dots, 0);
	set_arr_dot(&dots, NULL);
	set_centre(&dots, centre);
	
	return dots;
}

link_t init_links() {
	link_t link;
	set_links_count(&link, 0);
	set_arr_vec(&link, NULL);
	
	return link;
}

model_t init_model() {
	model_t mod;
	set_model_dots(&mod, init_dots());
	set_model_links(&mod, init_links());
	
	return mod;
}

void RotateX(dot_t* dot, double Alpha, dot_t centre) {
	Alpha *= M_PI / 180;
	dot_t buff = *dot;
	set_coord(dot, X_NAME, centre.X + (buff.X - centre.X));
	set_coord(dot, Y_NAME, centre.Y + (buff.Y - centre.Y) * cos(Alpha) + (buff.Z - centre.Z) * sin(Alpha));
	set_coord(dot, Z_NAME, centre.Z + (buff.Y - centre.Y) * sin(-Alpha) + (buff.Z - centre.Z) * cos(Alpha));
	
	return;
}

void RotateY(dot_t* dot, double Alpha, dot_t centre) {
	Alpha *= M_PI / 180;
	dot_t buff = *dot;
	set_coord(dot, X_NAME, centre.X + (buff.X - centre.X) * cos(Alpha) + (buff.Z - centre.Z) * sin(Alpha));
	set_coord(dot, Y_NAME, centre.Y + (buff.Y - centre.Y));
	set_coord(dot, Z_NAME, centre.Z + (buff.X - centre.X) * sin(-Alpha) + (buff.Z - centre.Z) * cos(Alpha));
	
	return;
}


void Scale(dot_t* dot, double Scale, dot_t centre) {
	set_coord(dot, centre.X + (dot->X - centre.X) * Scale,
	          centre.Y + (dot->Y - centre.Y) * Scale,
	          centre.Z + (dot->Z - centre.Z) * Scale);
	
	return;
}

void MoveOX(dot_t* dot, double Move) {
	double X = get_coord(*dot, X_NAME);
	X += Move;
	set_coord(dot, X_NAME, X);
	
	return;
}

void MoveOY(dot_t* dot, double Move) {
	double Y = get_coord(*dot, Y_NAME);
	Y += Move;
	set_coord(dot, Y_NAME, Y);
	
	return;
}

errs_num Dots_Change(dots_t* dots, change_t* change) {
	if (get_dots_count(*dots) == 0) {
		return ERR_ZERO;
	}
	
	Change_centre(dots, *change);
	Change_all_dots(dots, *change);
	Zero_change(change);
	
	return NO_ERR;
}

void Change_all_dots(dots_t* dots, change_t ch) {
	for (size_t i = 0; i < get_dots_count(*dots); i++) {
		dot_t dot = get_dot(*dots, i);
		recalculate_dot(&dot, *dots, ch);
		set_dot(dots, i, dot);
	}
}

void recalculate_dot(dot_t* dot, dots_t dots, change_t ch) {
	double j;
	
	if (j = get_change_t(moveOX, ch)) {
		MoveOX(dot, j);
	}
	
	if (j = get_change_t(moveOY, ch)) {
		MoveOY(dot, j);
	}
	
	if (j = get_change_t(angleOX, ch)) {
		RotateX(dot, j, get_dot_centre(dots));
	}
	
	if (j = get_change_t(angleOY, ch)) {
		RotateY(dot, j, get_dot_centre(dots));
	}
	
	if ((j = get_change_t(scale, ch)) != 1) {
		Scale(dot, j, get_dot_centre(dots));
	}
}

void Change_centre(dots_t* dots, change_t ch) {
	double j;
	
	if (j = get_change_t(moveOX, ch)) {
		MoveOX(&(dots->centre), j);
	}
	
	if (j = get_change_t(moveOY, ch)) {
		MoveOY(&(dots->centre), j);
	}
}

void Zero_change(change_t* change) {
	set_change_t(change, angleOX, 0);
	set_change_t(change, angleOY, 0);
	set_change_t(change, moveOX, 0);
	set_change_t(change, moveOY, 0);
	set_change_t(change, scale, 1);
}

link_t* get_links(model_t* mod) {
	return &(mod->links);
}


double get_change_t(change_const choose, change_t change) {
	switch (choose) {
		
		case moveOX:
			return change.moveOX;
		
		case moveOY:
			return change.moveOY;
		
		case scale:
			return change.scale;
		
		case angleOX:
			return change.angleOX;
		
		case angleOY:
			return change.angleOY;
		
		default:
			return NULL;
	}
}


void set_model_dots(model_t* mod, dots_t value) {
	mod->dots = value;
}

void set_model_links(model_t* mod, link_t value) {
	mod->links = value;
}

void set_change_t(change_t* change, change_const choose, double value) {
	switch (choose) {
		
		case moveOX:
			change->moveOX = value;
			break;
			
		case moveOY:
			change->moveOY = value;
			break;
			
		case angleOX:
			change->angleOX = value;
			break;
			
		case angleOY:
			change->angleOY = value;
			break;
			
		case scale:
			change->scale = value;
			break;
			
		default:
			break;
	}
}


void Init_center_model(dots_t* dots) {
	double X_max = get_max(*dots, X_NAME),
			X_min = get_min(*dots, X_NAME);
	
	double Y_max = get_max(*dots, Y_NAME),
			Y_min = get_min(*dots, Y_NAME);
	
	double Z_max = get_max(*dots, Z_NAME),
			Z_min = get_min(*dots, Z_NAME);
	
	dot_t buff_dot;
	set_coord(&buff_dot, (X_max + X_min) / 2, (Y_max + Y_min) / 2, (Z_max + Z_min) / 2);
	set_centre(dots, buff_dot);
}

double get_max(dots_t dots, coord_const coord_name) {
	double max = get_coord(get_dot(dots, 0), coord_name);
	
	for (size_t i = 0; i < get_dots_count(dots); ++i) {
		double buff = get_coord(get_dot(dots, i), coord_name);
		
		if (max < buff) {
			max = buff;
		}
	}
	
	return max;
}

double get_min(dots_t dots, coord_const coord_name) {
	double min = get_coord(get_dot(dots, 0), coord_name);
	
	for (size_t i = 0; i < get_dots_count(dots); ++i) {
		double buff = get_coord(get_dot(dots, i), coord_name);
		
		if (min > buff) {
			min = buff;
		}
	
	}
	return min;
}


dots_t* get_dots(model_t* mod) {
	return &(mod->dots);
}
