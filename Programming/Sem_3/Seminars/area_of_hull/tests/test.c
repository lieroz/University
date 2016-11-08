#include <stdio.h>
#include <stdbool.h>
#include "../functions.h"

int main(){
	char* names[] = {
				"test1.txt",
				"test2.txt",
				"test3.txt",
				"test4.txt",
				"test5.txt",
				"test6.txt",
				"test7.txt"
			};

	int count = sizeof(names) / sizeof(*names);

	FILE* f[count];
	for (int i = 0; i < count; i++){
		fprintf(stdout, "-------------------------------------------\n");
		fprintf(stdout, "DATA FOR TEST NUMBER %d:\n\n", i + 1);
		f[i] = fopen(names[i], "r");
		bool convex = checkConvexity(f[i]);
		if (!convex){
			fprintf(stdout, "Convex || self-intersecting polygon: FALSE\n\n");
			rewind(f[i]);

			double area = getArea(f[i], true);
			fprintf(stdout, "The area of nonconvex polygon is: %lf\n\n", area);
		} else{
			fprintf(stdout, "Convex || self-intersecting polygon: TRUE\n\n");
		}

		fclose(f[i]);
	}


	return 0;
}
