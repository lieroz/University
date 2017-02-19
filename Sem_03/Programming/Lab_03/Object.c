#include "Object.h"

// Public list methods
void AddObjectToDictionary(Dictionary* dict, Object* object) {
	struct ObjectNode* node = (struct ObjectNode*) malloc(sizeof(struct ObjectNode));

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

	++dict->count;
}

void PrintDictionary(const Dictionary* dict) {
	struct ObjectNode* current = dict->head;
	while (current != NULL) {
		fprintf(stdout, "%d\n", current->object->OBJECT_FEATURE_1);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_2);
		fprintf(stdout, "%d\n", current->object->OBJECT_FEATURE_3);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_4);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_5);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_6);
		fprintf(stdout, "%lf\n\n", current->object->OBJECT_FEATURE_7);
		current = current->next;
	}
}

void FreeDictionary(Dictionary* dict) {
	struct ObjectNode* current = dict->head;
	while (current) {
		struct ObjectNode* next = current->next;
		free(current->object->OBJECT_FEATURE_2);
		free(current->object->OBJECT_FEATURE_4);
		free(current->object->OBJECT_FEATURE_5);
		free(current->object->OBJECT_FEATURE_6);
		free(current->object);
		free(current);
		current = next;
	}

	dict->head = dict->tail = 0;
}

// Parser part
void AssignValues(Object* object, char* buffer, int index) {
	switch (index) {
		case 1:
			sscanf(buffer, "%d", &object->OBJECT_FEATURE_1);
			free(buffer);
			break;
		case 2:
			object->OBJECT_FEATURE_2 = buffer;
			break;
		case 3:
			sscanf(buffer, "%d", &object->OBJECT_FEATURE_3);
			free(buffer);
			break;
		case 4:
			object->OBJECT_FEATURE_4 = buffer;
			break;
		case 5:
			object->OBJECT_FEATURE_5 = buffer;
			break;
		case 6:
			object->OBJECT_FEATURE_6 = buffer;
			break;
		case 7:
			sscanf(buffer, "%lf", &object->OBJECT_FEATURE_7);
			free(buffer);
			break;
	}
}

bool IsSeparator(char symbol) {
	if (symbol == ' ' || symbol == '\n' || symbol == EOF) {
		return true;
	}

	return false;
}

Dictionary FillDictionary(FILE* f) {
	Dictionary dict;
	dict.count = 0;
	dict.head = dict.tail = 0;

	Object* object = (Object*) malloc(sizeof(Object));

	int current_index = 0;
	int onset = 0;
	int i = 0;
	while (!feof(f)) {
		++current_index;

		char symbol = fgetc(f);
		if (symbol == '<') {

			while (symbol != '>') {
				++current_index;
				symbol = fgetc(f);
			}

			continue;
		}

		else if (IsSeparator(symbol)) {
			continue;
		}

		else {
			++i;
			fseek(f, --current_index, SEEK_SET);
			onset = current_index;

			while (true) {
				symbol = fgetc(f);
				if (symbol == '<') {
					break;
				}
				++current_index;
			}

			fseek(f, onset, SEEK_SET);

			int element_length = current_index - onset;
			char* buffer = (char*) malloc(sizeof(char) * (element_length + 1));
			for (int i = 0; i < element_length; ++i) {
				buffer[i] = fgetc(f);
			}
			buffer[element_length] = '\0';

			AssignValues(object, buffer, i);
			if (i == OBJECT_FEATURE_COUNT) {
				AddObjectToDictionary(&dict, object);
				i = 0;
				object = (Object*) malloc(sizeof(Object));
			}

			fseek(f, current_index, SEEK_SET);
		}
	}

	return dict;
}

// Quicksort for doubly-linked list
void Swap(struct ObjectNode* a, struct ObjectNode* b) {
	struct ObjectNode temp = *a;
	a->object = b->object;
	b->object = temp.object;
}

struct ObjectNode* Partition(struct ObjectNode* left, struct ObjectNode* right, int (*cmp)(const void*, const void*)) {
	struct ObjectNode* i = left->prev;

	for (struct ObjectNode* j = left; j != right; j = j->next) {
		if (cmp(j, right) < 0) {
			i = (i == NULL) ? left : i->next;
			Swap(i, j);
		}
	}

	i = (i == NULL) ? left : i->next;
	Swap(i, right);
	return i;
}

void _QuickSort(struct ObjectNode* left, struct ObjectNode* right, int (*cmp)(const void*, const void*)) {
	if (right != NULL && left != right && left != right->next) {
		struct ObjectNode* p = Partition(left, right, cmp);
		_QuickSort(left, p->prev, cmp);
		_QuickSort(p->next, right, cmp);
	}
}

void QuickSort(Dictionary* dict, int (*cmp)(const void*, const void*)) {
	_QuickSort(dict->head, dict->tail, cmp);
}

// Comparators
int int_comparator(const void* obj_1, const void* obj_2) {
	const struct ObjectNode* temp_obj_1 = (const struct ObjectNode*)obj_1;
	const struct ObjectNode* temp_obj_2 = (const struct ObjectNode*)obj_2;
	int result = temp_obj_1->object->OBJECT_FEATURE_3 - temp_obj_2->object->OBJECT_FEATURE_3;

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	}

	return 0;
}

int double_comparator(const void* obj_1, const void* obj_2) {
	const struct ObjectNode* temp_obj_1 = (const struct ObjectNode*)obj_1;
	const struct ObjectNode* temp_obj_2 = (const struct ObjectNode*)obj_2;
	double result = temp_obj_1->object->OBJECT_FEATURE_7 - temp_obj_2->object->OBJECT_FEATURE_7;

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	}

	return 0;
}

int string_comparator(const void* obj_1, const void* obj_2) {
	const struct ObjectNode* temp_obj_1 = (const struct ObjectNode*)obj_1;
	const struct ObjectNode* temp_obj_2 = (const struct ObjectNode*)obj_2;

	return strcmp(temp_obj_1->object->OBJECT_FEATURE_2, temp_obj_2->object->OBJECT_FEATURE_2);
}

// Search function
int SearchEmployeeID(const Dictionary* dict, const int compared_element) {
	struct ObjectNode* current = dict->head;
	int index = 0;

	while (current != NULL && (current->object->OBJECT_FEATURE_3 - compared_element)){
		++index;
		current = current->next;
	}

	if (current == NULL) {
		return -1;
	}

	return index;
}

int SearchFreight(const Dictionary* dict, const double compared_element) {
	struct ObjectNode* current = dict->head;
	int index = 0;

	while (current != NULL && (current->object->OBJECT_FEATURE_7 - compared_element)){
		++index;
		current = current->next;
	}

	if (current == NULL) {
		return -1;
	}

	return index;
}

int SearchCustomerID(const Dictionary* dict, const char* compared_element) {
	struct ObjectNode* current = dict->head;
	int index = 0;

	while (current != NULL && strcmp(current->object->OBJECT_FEATURE_2, compared_element)){
		++index;
		current = current->next;
	}

	if (current == NULL) {
		return -1;
	}

	return index;
}