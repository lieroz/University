#ifndef ACTION
#define ACTION

#include "geometry.h"
#include "print_picture.h"
#include "error.h"
#include "load_file.h"
#include "print_picture.h"
#include "ptr.h"

typedef union {
	char* load_act;
	change_t modi_act;
	drawing_act draw_act;
} argument;

char* get_load_act(argument arg);
change_t* get_modi_act(argument* arg);
drawing_act get_draw_act(argument arg);

void set_arg_load_act(argument* arg, char* load_act);
void set_arg_modi_act(argument* arg, change_t modi_act);
void set_arg_draw_act(argument* arg, drawing_act draw_act);

//errs_num Clear_load_act(argument arg);

errs_num Read_Model_proc(model_t* mod, argument arg);
errs_num Change_Dots_proc(model_t* mod, argument* arg);
errs_num Print_proc(model_t* mod, argument arg);
errs_num Clear_ALL(model_t* mod);


#endif // ACTION

