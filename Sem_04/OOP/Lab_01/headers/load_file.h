#ifndef LOAD_FILE
#define LOAD_FILE

#include <stdio.h>
#include "geometry.h"
#include "stream.h"
#include "error.h"

errs_num Read_Model(model_t* mod, char* name);
errs_num Read_model_from_stream(model_t* mod, Stream S);

int _get_count(size_t* count, Stream S);
errs_num Get_count(size_t* count, Stream S);

int _get_dot(double* x, double* y, double* z, Stream S);
errs_num Get_dot(dot_t* dot, Stream S);

int _get_vec(size_t* st, size_t* fin, Stream S);
errs_num Get_vec(vec_t* vec, Stream S);

errs_num Read_Model_dots(dots_t* dots, Stream S);
errs_num Read_Model_links(link_t* link, Stream S);

errs_num _get_dots(dots_t* dots, Stream S, size_t count);
errs_num _get_links(link_t* link, Stream S, size_t count);

#endif // LOAD_FILE

