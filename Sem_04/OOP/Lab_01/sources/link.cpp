#include "link.h"
#include "ptr.h"

void set_vec_S(vec_t* vec, size_t value) {
	vec->S = value;
}

void set_vec_F(vec_t* vec, size_t value) {
	vec->F = value;
}

size_t get_vec_S(vec_t link) {
	return link.S;
}

size_t get_vec_F(vec_t link) {
	return link.F;
}

void set_arr_vec(link_t* links, vec_t* ptr) {
	links->link = ptr;
}

void set_vec(link_t* links, int i, vec_t value) {
	links->link[i] = value;
}

void set_links_count(link_t* links, size_t value) {
	links->count = value;
}

void* get_arr_vec(link_t links) {
	return (void*) links.link;
}

vec_t get_vec(link_t link, int i) {
	return link.link[i];
}

size_t get_links_count(link_t link) {
	return link.count;
}

int clear_arr_vec(link_t* links) {
	Clear_Ptr((void*) links->link);
	
	return 0;
}
