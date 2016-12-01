#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 20

typedef struct {
	char* last_name;
	char* first_name;
	char* middle_name;
} Person;

struct Node {
	Person* object;

	struct Node* next;
	struct Node* prev;
};

typedef struct {
	int count;

	struct Node* head;
	struct Node* tail; 
} Dictionary;

void AddObjectToDictionary(Dictionary* dict, Person* object) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));

	node->object = object;

	if (dict->tail) {
		dict->tail->next = node;
	}

	node->next = NULL;
	node->prev = dict->tail;
	dict->tail = node;

	if (dict->head == NULL) {
		dict->head = node;
	}
}

Dictionary GetPersons(FILE *f) {
	Dictionary result;
	result.count = 0;
	result.head = result.tail = NULL;

	fscanf(f, "%d", &result.count);

	for (int i = 0; i < result.count; ++i) {
		Person* person = (Person*) malloc(sizeof(Person));

		char* buf1 = (char*) malloc(sizeof(char) * STR_LEN);
		char* buf2 = (char*) malloc(sizeof(char) * STR_LEN);
		char* buf3 = (char*) malloc(sizeof(char) * STR_LEN);

		fscanf(f, "%s", buf1);
		fscanf(f, "%s", buf2);
		fscanf(f, "%s", buf3);

		person->last_name = buf1;
		person->first_name = buf2;
		person->middle_name = buf3;

		AddObjectToDictionary(&result, person);
	}

	return result;
}

void Print(Dictionary dict, FILE* f) {
	for (struct Node* i = dict.head; i != NULL; i = i->next) {
		fprintf(f, "%s %s %s\n", i->object->last_name, i->object->first_name, i->object->middle_name);
	}
}

void FreeNodes(Dictionary dict) {
	struct Node* p = dict.head;

	while (p){
		struct Node* next = p->next;
		free(p->object->first_name);
		free(p->object->last_name);
		free(p->object->middle_name);
		free(p->object);
		free(p);
		p = next;
	}

	dict.head = dict.tail = NULL;
}

// Quicksort for doubly-linked list
void Swap(struct Node* a, struct Node* b) {
	struct Node temp = *a;
	a->object = b->object;
	b->object = temp.object;
}

struct Node* Partition(struct Node* left, struct Node* right, int (*cmp)(const void*, const void*)) {
	struct Node* i = left->prev;

	for (struct Node* j = left; j != right; j = j->next) {
		if (cmp(j, right) < 0) {
			i = (i == NULL) ? left : i->next;
			Swap(i, j);
		}
	}

	i = (i == NULL) ? left : i->next;
	Swap(i, right);
	return i;
}

void _QuickSort(struct Node* left, struct Node* right, int (*cmp)(const void*, const void*)) {
	if (right != NULL && left != right && left != right->next) {
		struct Node* p = Partition(left, right, cmp);
		_QuickSort(left, p->prev, cmp);
		_QuickSort(p->next, right, cmp);
	}
}

void QuickSort(Dictionary* dict, int (*cmp)(const void*, const void*)) {
	_QuickSort(dict->head, dict->tail, cmp);
}

int string_comparator(const void* obj_1, const void* obj_2) {
	const struct Node* temp_obj_1 = (const struct Node*)obj_1;
	const struct Node* temp_obj_2 = (const struct Node*)obj_2;

	return strcmp(temp_obj_1->object->last_name, temp_obj_2->object->last_name);
}

int main(const int agrc, const char* argv[]) {
	FILE* f = fopen(argv[1], "r");
	FILE* f2 = fopen(argv[2], "w");

	Dictionary dict = GetPersons(f);

	for (struct Node* i = dict.head; i != NULL; i = i->next) {

		for (struct Node* j = i->next; j != NULL; j = j->next) {

			if (strcmp(i->object->first_name, j->object->last_name) == 0) {
				char* temp = j->object->middle_name;
				j->object->middle_name = j->object->first_name;
				j->object->first_name = j->object->last_name;
				j->object->last_name = temp;
			}

			if (strcmp(i->object->last_name, j->object->first_name) == 0) {
				char* temp = i->object->middle_name;
				i->object->middle_name = i->object->first_name;
				i->object->first_name = i->object->last_name;
				i->object->last_name = temp;
			}
		}
	}

	QuickSort(&dict, string_comparator);

	Print(dict, f2);
	FreeNodes(dict);

	fclose(f);

	return 0;
}