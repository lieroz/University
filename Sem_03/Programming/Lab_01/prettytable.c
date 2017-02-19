#include "prettytable.h"

bool isSpace(char ch){
	if (ch == ' ' || ch == '\t') return true;
	return false;
}

bool newLine(char ch){
	if (ch == '\n') return true;
	return false;
}

bool isDigit(char ch){
	char nums[] = "0123456789";
	int size = (int)sizeof(nums);
	for (int i = 0; i < size; ++i){
		if (ch == nums[i]) return true;
	}
	return false;
}

bool isDot(char ch){
	if (ch == '.') return true;
	return false;
}

int getStrCount(void* stream){
	char ch;
	int strCount = 0;
	while (!feof(stream)){
		fscanf(stream, "%c", &ch);
		if (newLine(ch)){
			strCount++;
		}
	}

	rewind(stream);
	return strCount;
}

int getColCount(void* stream){
	char ch;
	int colCount = 0;
	int curPos = 1;

	fscanf(stream, "%c", &ch);
	while (!newLine(ch)){
		++curPos;
		if (!isSpace(ch)){
			fscanf(stream, "%c", &ch);
			if (isSpace(ch)){
				++colCount;
			}
			fseek(stream, curPos - 1, SEEK_SET);
		}
		fscanf(stream, "%c", &ch);
	}

	++colCount;
	rewind(stream);

	return colCount;
}

int* getColWidths(void* stream){
	int colCount = getColCount(stream);	
	int* colWidths = (int*)malloc(sizeof(int) * colCount);

	int curCol = 0;
	int flag = 1;
	int curPos = 1;

	int curWidth;
	char ch;
	while (!feof(stream)){
		++curPos;
		fscanf(stream, "%c", &ch);

		if (isSpace(ch)){
			curWidth = curPos - flag - 1;

			if (curWidth > colWidths[curCol])
				colWidths[curCol] = curWidth;

			flag = curPos;

			fscanf(stream, "%c", &ch);
			if (!isSpace(ch)){
				++curPos;
				++curCol;
			}
		}

		if (newLine(ch)){
			curWidth = curPos - flag - 1;

			if (curWidth > colWidths[curCol])
				colWidths[curCol] = curWidth;

			flag = curPos;

			fscanf(stream, "%c", &ch);
			if (!isSpace(ch)){
				++curPos;
				++curCol;
			}

			curCol = 0;
		}
	}
	rewind(stream);
	return colWidths;
}

void printTable(void* stream){
	int strCount = getStrCount(stream);
	int colCount = getColCount(stream);
	int* colWidths = getColWidths(stream);

	for (int i = 0; i < 2 * strCount - 1; ++i){
		if (!(i % 2)){
			fprintf(stdout, "+");
			for (int j = 0; j < colCount; ++j){
				int curWidth = colWidths[j] + 6;
				for (int k = 0; k < curWidth; ++k){
					fprintf(stdout, "-");
				}
				fprintf(stdout, "+");
			}
		} else{
			fprintf(stdout, "| ");
			for (int j = 0; j < colCount; ++j){
				int curWidth = colWidths[j] + 4;
				char* str = (char*)malloc(sizeof(char) * (curWidth - 4));
				fscanf(stream, "%s", str);

				int size = (int)strlen(str);
				int count = 0;
				int dot = 0;
				for (int k = 0; k < size; k++){
					if (isDigit(str[k])) ++count;
					if (isDot(str[k])) dot = k;
				}

				if (count == size){
					fprintf(stdout, "%*s", curWidth, str);
				} else if (size == 1){
					if ((curWidth % 2) == 0)
						fprintf(stdout, "%*s%*s", curWidth / 2, str, curWidth / 2, " ");
					else
						fprintf(stdout, "%*s%*s", curWidth / 2 + 1, str, curWidth / 2, " ");
				} else if (count + 1 == size){
					int realSize = size - dot - 1;
					char* fraction = (char*)malloc(sizeof(char) * realSize);
					int intSize = size - realSize - 1;
					char* integral = (char*)malloc(sizeof(char) * intSize);

					for (int w = 0; w < dot; ++w){
						integral[w] = str[w];
					}

					for (int w = dot + 1; w < size; ++w){
						fraction[w - dot - 1] = str[w];
					}

					if (strlen(fraction) < 2){
						for (int i = strlen(fraction); i < 2; i++){
							fraction[i] = '0';
						}
					}
					
					fprintf(stdout, "%*s", curWidth - 3, integral);
					fprintf(stdout, "%c", str[dot]);
					fprintf(stdout, "%.2s", fraction);
					// fprintf(stdout, "%*s", curWidth / 2 - 1, integral);
					// fprintf(stdout, "%c", str[dot]);
					// if ((curWidth % 2) == 0)
					// 	fprintf(stdout, "%-*.*s", curWidth / 2, curWidth / 2, fraction);
					// else
					// 	fprintf(stdout, "%-*.*s", curWidth / 2 + 1, curWidth / 2, fraction);

					/* Something odd happens here, when memory is freed,
					junk is getting into the console */
					// free(integral);
					// free(fraction);
				} else{
					fprintf(stdout, "%-*s", curWidth, str);
				}

				free(str);
				fprintf(stdout, " | ");
			}
		}
		fprintf(stdout, "\n");
	}
	free(colWidths);
}