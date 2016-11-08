#include <stdio.h>
#include "Object.h"

#define NOT_ENOUGH_ARGUMENTS 0
#define INVALID_ARGUMENT     0

int main(const int argc, const char** argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: NOT_ENOUGH_ARGUMENTS!!!\n");
		return NOT_ENOUGH_ARGUMENTS;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f) {
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		return INVALID_ARGUMENT;
	}

	Dictionary dict = FillDictionary(f);

	fprintf(stdout, "Enter {0, 1, 2} to sort by {EmployeeID, Freight, CustomerID}: ");

	int choice = 0;
	if (fscanf(stdin, "%d", &choice) != 1) {
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		return INVALID_ARGUMENT;		
	}
	fprintf(stdout, "\n");

	int index = 0;

	if (choice == 0) {
		QuickSort(&dict, int_comparator);

		fprintf(stdout, "Type EmployeeID to search: ");

		int employee_ID = 0;
		if (fscanf(stdin, "%d", &employee_ID) != 1) {
			fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
			return INVALID_ARGUMENT;			
		}

		index = SearchEmployeeID(&dict, employee_ID);
	} else if (choice == 1) {
		QuickSort(&dict, double_comparator);

		fprintf(stdout, "Type Freight to search: ");

		double freight = 0;
		if (fscanf(stdin, "%lf", &freight) != 1) {
			fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
			return INVALID_ARGUMENT;			
		}

		index = SearchFreight(&dict, freight);
	} else if (choice == 2) {
		QuickSort(&dict, string_comparator);

		fprintf(stdout, "Type CustomerID to search: ");

		char customer_ID[6];
		if (fscanf(stdin, "%s", customer_ID) != 1) {
			fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
			return INVALID_ARGUMENT;			
		}

		index = SearchCustomerID(&dict, customer_ID);
	} else {
		fprintf(stdout, "Ommiting sorting and searching of the list.\n\n");
	}


	PrintDictionary(&dict);
	fprintf(stdout, "First index of searched element: %d\n", index);
	
	FreeDictionary(&dict);
	fclose(f);

	return 0;
}