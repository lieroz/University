#include "load_file.h"
#include "ptr.h"
#include "action.h"


errs_num Read_Model(model_t* mod, char* name) {
	Stream stream;
	
	if (!open_stream(&stream, name)) {
		return ERR_WITH_FILE;
	}
	
	errs_num err = NO_ERR;
	model_t mod_buff;
	
	if ((err = Read_model_from_stream(&mod_buff, stream)) != NO_ERR) {
		Close_Stream(&stream);
		
		return err;
	}
	
	Close_Stream(&stream);
	err = Clear_ALL(mod);
	*mod = mod_buff;
	
	return err;
}


errs_num Read_model_from_stream(model_t* mod, Stream S) {
	dots_t dots;
	link_t link;
	errs_num err = NO_ERR;
	
	if ((err = Read_Model_dots(&dots, S)) != NO_ERR) {
		return err;
	}
	
	Init_center_model(&dots);
	
	if ((err = Read_Model_links(&link, S)) != NO_ERR) {
		clear_arr_dot(&dots);
		return err;
	}
	
	set_model_dots(mod, dots);
	set_model_links(mod, link);
	
	return err;
}


int _get_count(size_t* count, Stream S) {
	return fscanf(get_stream(S), "%lu", count);
}

errs_num Get_count(size_t* count, Stream S) {
	if (_get_count(count, S) != 1) {
		return ERR_WITH_FILE;
	}
	
	return NO_ERR;
}


int _get_dot(double* x, double* y, double* z, Stream S) {
	return fscanf(get_stream(S), "%lf %lf %lf", x, y, z);
}

errs_num Get_dot(dot_t* dot, Stream S) {
	double x, y, z;
	
	if (_get_dot(&x, &y, &z, S) != 3) {
		return ERR_WITH_FILE;
	}
	
	set_coord(dot, x, y, z);
	return NO_ERR;
}


int _get_vec(size_t* st, size_t* fin, Stream S) {
	return fscanf(get_stream(S), "%lu %lu", st, fin);
}

errs_num Get_vec(vec_t* vec, Stream S) {
	size_t st, fin;
	
	if (_get_vec(&st, &fin, S) != 2) {
		return ERR_WITH_FILE;
	}
	
	set_vec_F(vec, fin);
	set_vec_S(vec, st);
	
	return NO_ERR;
}

errs_num Read_Model_dots(dots_t* dots, Stream S) {
	errs_num err = NO_ERR;
	void* ptr = NULL;
	
	size_t count_dots = 0;
	
	if ((err = Get_count(&count_dots, S)) != NO_ERR) {
		return err;
	}
	
	if (!(ptr = Get_mem(sizeof(dot_t), count_dots))) {
		ptr = NULL;
		
		return err = ERR_WITH_MEMORY;
	}
	
	set_arr_dot(dots, (dot_t*) ptr);
	set_count(dots, count_dots);
	
	err = _get_dots(dots, S, count_dots);
	
	if (err != NO_ERR) {
		Clear_Ptr(get_arr_dot(*dots));
		set_arr_dot(dots, NULL);
		
		return err = ERR_WITH_FILE;
	}
	
	return err;
}

errs_num _get_dots(dots_t* dots, Stream S, size_t count) {
	errs_num err = NO_ERR;
	dot_t buff_dot;
	
	for (size_t i = 0; i < count && ((err = Get_dot(&buff_dot, S)) == NO_ERR); ++i) {
		set_dot(dots, i, buff_dot);
	}
	
	return err;
}

errs_num Read_Model_links(link_t* link, Stream S) {
	errs_num err = NO_ERR;
	void* ptr = NULL;
	size_t count_links = 0;
	
	if ((err = Get_count(&count_links, S)) != NO_ERR) {
		
		return err;
	}
	
	if (!(ptr = Get_mem(sizeof(vec_t), count_links))) {
		ptr = NULL;
		
		return err = ERR_WITH_MEMORY;
	}
	
	set_arr_vec(link, (vec_t*) ptr);
	set_links_count(link, count_links);
	
	err = _get_links(link, S, count_links);
	
	if (err != NO_ERR) {
		Clear_Ptr(get_arr_vec(*link));
		set_arr_vec(link, NULL);
		
		return err = ERR_WITH_FILE;
	}
	
	return err;
}

errs_num _get_links(link_t* link, Stream S, size_t count) {
	errs_num err = NO_ERR;
	vec_t buff_vec;
	
	for (size_t i = 0; i < count &&
	                         ((err = Get_vec(&buff_vec, S)) == NO_ERR) &&
	                         get_vec_S(buff_vec) < count &&
	                         get_vec_F(buff_vec) < count; ++i) {
		                         set_vec(link, i, buff_vec);
	}
	
	return err;
}

