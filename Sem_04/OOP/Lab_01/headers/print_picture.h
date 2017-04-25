#ifndef PRINT_PICTURE
#define PRINT_PICTURE

#include "geometry.h"
#include <QGraphicsScene>

typedef struct {
	QGraphicsScene* scene;
	int width;
	int height;
} drawing_act;

QGraphicsScene* get_scene(drawing_act act);
int get_width(drawing_act act);
int get_height(drawing_act act);

void set_scene(drawing_act* act, QGraphicsScene* scene);
void set_width(drawing_act* act, int value);
void set_height(drawing_act* act, int value);

void clear_scene(drawing_act act);

errs_num Print_3D_to_2D(model_t* mod, drawing_act act);
void lineto(drawing_act act, dot_t S, dot_t F);
void Clear_scene(drawing_act act);

#endif // PRINT_PICTURE

