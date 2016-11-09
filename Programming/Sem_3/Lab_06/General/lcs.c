#include "lcs.h"

LCS* Constructor(int h, int w) {
	LCS* lcs = (LCS*) malloc(sizeof(LCS));

	lcs->matrix = (int**) malloc(sizeof(int*) * (h + 1));
	lcs->symbols = (char**) malloc(sizeof(char*) * (h + 1));

	for (int i = 0; i <= h ; ++i) {
		lcs->matrix[i] = (int*) malloc(sizeof(int) * (w + 1));
		lcs->symbols[i] = (char*) malloc(sizeof(char) * (w + 1));
	}

	lcs->height = h;
	lcs->width = w;

	return lcs;
}

void Destructor(LCS* lcs) {
	for (int i = 0; i <= lcs->height ; ++i) {
		free(lcs->matrix[i]);
		free(lcs->symbols[i]);
	}
	free(lcs->matrix);
	free(lcs->symbols);

	lcs->matrix = NULL;
	lcs->symbols = NULL;
	lcs->height = 0;
	lcs->width = 0;

	free(lcs);
	lcs = NULL;
}

LCS* LCS_Length(char* X, char* Y) {
	int x_length = strlen(X);
	int y_length = strlen(Y);

	LCS* lcs = Constructor(x_length, y_length);

	for (int i = 0; i <= x_length; ++i) {
		lcs->matrix[i][0] = 0;
	}

	for (int j = 0; j <= y_length; ++j) {
		lcs->matrix[0][j] = 0;
	}

	for (int i = 1; i <= x_length; ++i) {
		
		for (int j = 1; j <= y_length; ++j) {
			
			if (X[i - 1] == Y[j - 1]) {
				lcs->matrix[i][j] = lcs->matrix[i - 1][j - 1] + 1;
				lcs->symbols[i][j] = '\\';
			} else if (lcs->matrix[i - 1][j] >= lcs->matrix[i][j - 1]) {
				lcs->matrix[i][j] = lcs->matrix[i - 1][j];
				lcs->symbols[i][j] = '|';
			} else {
				lcs->matrix[i][j] = lcs->matrix[i][j - 1];
				lcs->symbols[i][j] = '-';
			}
		}
	}

	return lcs;
}

void PrintLCS(LCS* lcs, char* str, int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}

	if (lcs->symbols[i][j] == '\\') {
		PrintLCS(lcs, str, i - 1, j - 1);
		fprintf(stdout, "%c", str[i - 1]);
	} else if (lcs->symbols[i][j] == '|') {
		PrintLCS(lcs, str, i - 1, j);
	} else {
		PrintLCS(lcs, str, i, j - 1);
	}
}