#include "action.h"

errs_num Print_proc(model_t* mod, argument arg) {
	return Print_3D_to_2D(mod, get_draw_act(arg));
}

errs_num Change_Dots_proc(model_t* mod, argument* arg) {
	return Dots_Change(get_dots(mod), get_modi_act(arg));
}

errs_num Read_Model_proc(model_t* mod, argument arg) {
	return Read_Model(mod, get_load_act(arg));
}

char* get_load_act(argument arg) {
	return arg.load_act;
}

change_t* get_modi_act(argument* arg) {
	return &(arg->modi_act);
}

drawing_act get_draw_act(argument arg) {
	return arg.draw_act;
}

void set_arg_load_act(argument* arg, char* load_act) {
	arg->load_act = load_act;
}

void set_arg_modi_act(argument* arg, change_t modi_act) {
	arg->modi_act = modi_act;
}

void set_arg_draw_act(argument* arg, drawing_act draw_act) {
	arg->draw_act = draw_act;
}

errs_num Clear_ALL(model_t* mod) {
	errs_num err = NO_ERR;
	if (!clear_arr_dot(get_dots(mod))) {
		err = NO_ERR;
	}
	
	if (!clear_arr_vec(get_links(mod))) {
		err = NO_ERR;
	}
	
	return err;
}
