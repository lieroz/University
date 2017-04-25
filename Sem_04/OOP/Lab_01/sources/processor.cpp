#include "processor.h"

errs_num processor(argument* arg, action act) {
	static model_t mod = init_model();
	errs_num err = NO_ERR;
	
	switch (act) {
		
		case LOAD:
			err = Read_Model_proc(&mod, *arg);
			break;
			
		case CHANGE:
			err = Change_Dots_proc(&mod, arg);
			break;
			
		case DRAW:
			err = Print_proc(&mod, *arg);
			break;
			
		case CLEAR:
			err = Clear_ALL(&mod);
			break;
	}
	
	return err;
}

