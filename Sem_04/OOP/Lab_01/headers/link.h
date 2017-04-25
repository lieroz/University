#ifndef LINK
#define LINK

#include <cstddef>

typedef struct VEC_TYPE {
	size_t S;
	size_t F;
} vec_t;

void set_vec_S(vec_t* vec, size_t value);
void set_vec_F(vec_t* vec, size_t value);

size_t get_vec_S(vec_t link);
size_t get_vec_F(vec_t link);

typedef struct LINK_TYPE {
	vec_t* link;
	size_t count;
} link_t;

void set_arr_vec(link_t* links, vec_t* ptr);
void set_vec(link_t* links, int i, vec_t value);
void set_links_count(link_t* links, size_t value);

void* get_arr_vec(link_t links);
vec_t get_vec(link_t link, int i);
size_t get_links_count(link_t link);

int clear_arr_vec(link_t* links);

#endif // LINK

