#include "lineto.h"

void lineto(drawing_act act, dot_t S, dot_t F) {
	int cent_y = get_height(act) / 2;
	int cent_x = get_width(act) / 2;
	QGraphicsScene* model_scene = get_scene(act);
	
	model_scene->addLine(cent_x + get_coord(S, X_NAME), cent_y - get_coord(S, Y_NAME),
	                     cent_x + get_coord(F, X_NAME), cent_y - get_coord(F, Y_NAME));
}
