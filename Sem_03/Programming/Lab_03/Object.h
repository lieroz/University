#ifndef __ORDERS_H_DEF__
#define __ORDERS_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Change this to change your object features.
// 	You will have to change lines 21 - 29 in Object.h,
// if you wanna another features of object.

// 	Also you will have to rebuild functions: PrintDictionary (lines 23 - 35),
// FreeDictionary (lines 37 - 51) & AssignValues (lines 53 - 80) in file Object.c.
#define OBJECT_FEATURE_COUNT 7

#define OBJECT_FEATURE_1      order_ID
#define OBJECT_FEATURE_2   customer_ID
#define OBJECT_FEATURE_3   employee_ID
#define OBJECT_FEATURE_4    order_date
#define OBJECT_FEATURE_5 required_date
#define OBJECT_FEATURE_6  shipped_date
#define OBJECT_FEATURE_7       freight

// Representation of object
typedef struct {
	int    OBJECT_FEATURE_1;
	char*  OBJECT_FEATURE_2;
	int    OBJECT_FEATURE_3;
	char*  OBJECT_FEATURE_4;
	char*  OBJECT_FEATURE_5;
	char*  OBJECT_FEATURE_6;
	double OBJECT_FEATURE_7;
} Object;

// Two-linked list to store data from file
// List node
struct ObjectNode {
	Object* object;

	struct ObjectNode* next;
	struct ObjectNode* prev;
};

// List head & tail
typedef struct {
	int count;

	struct ObjectNode* head;
	struct ObjectNode* tail; 
} Dictionary;

// Public methods
void AddObjectToDictionary(Dictionary*, Object*);
void PrintDictionary(const Dictionary*);
void FreeDictionary(Dictionary*);

// 'Parser' because it is not a parser
Dictionary FillDictionary(FILE*);

// Quicksort part
void QuickSort(Dictionary*, int (*cmp)(const void*, const void*));

// Comparators implementation
int int_comparator(const void*, const void*);
int double_comparator(const void*, const void*);
int string_comparator(const void*, const void*);

// Traversing through list and searching for element
int SearchEmployeeID(const Dictionary*, const int);
int SearchFreight(const Dictionary*, const double);
int SearchCustomerID(const Dictionary*, const char*);

#endif // __ORDERS_H_DEF__