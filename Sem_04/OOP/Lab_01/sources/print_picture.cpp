#include "print_picture.h"
#include "lineto.h"


errs_num Print_3D_to_2D(model_t* mod, drawing_act act) {
	dots_t dots = *get_dots(mod);
	
	if (get_dots_count(dots) == 0) {
		return ERR_ZERO;
	
	}
	
	link_t links = *get_links(mod);
	
	if (get_links_count(links) == 0) {
		return ERR_ZERO;
	}
	
	Clear_scene(act);
	
	for (size_t i = 0; i < get_links_count(links); i++) {
		dot_t S = get_dot(dots, get_vec_S(get_vec(links, i)));
		dot_t F = get_dot(dots, get_vec_F(get_vec(links, i)));
		lineto(act, S, F);
	
	}
	
	return NO_ERR;
}

void Clear_scene(drawing_act act) {
	get_scene(act)->clear();
}


QGraphicsScene* get_scene(drawing_act act) {
	return act.scene;
}

int get_width(drawing_act act) {
	return act.width;
}

int get_height(drawing_act act) {
	return act.height;
}

void set_scene(drawing_act* act, QGraphicsScene* scene) {
	act->scene = scene;
}

void set_width(drawing_act* act, int value) {
	act->width = value;
}

void set_height(drawing_act* act, int value) {
	act->height = value;
}

