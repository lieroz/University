#include "check_string.h"

bool IsValid(char symbol) {
	char valid_symbols[] = "0123456789"
				   "-+eE.";

	int size = sizeof(valid_symbols);
	for (int i = 0; i < size; ++i){
		if (symbol == valid_symbols[i]) return true;
	}

	return false;
}

bool IsValidNumber(char* number) {
	if (*number == '.' || *number == 'e') {
		return false;
	}

	int e_pos = 0;
	int dot_pos = 0;
	int sign_pos = 0;
	int size = strlen(number);
	for (int i = 0; i < size; ++i) {

		if (!IsValid(number[i])) {
			return false;
		}

		if (number[i] == '.') {
			dot_pos = i;
		}

		if (number[i] == 'e' || number[i] == 'E') {
			e_pos = i;
		}

		if (number[i] == '+' || number[i] == '-') {
			sign_pos = i;
		}
	}

	if ((dot_pos == 0 && e_pos == 0)) {
		return false;
	}

	if (e_pos != 0 && dot_pos > e_pos) {
		return false;
	}

	if (e_pos == size - 1) {
		return false;
	}

	if (sign_pos != 0 && (sign_pos - 1) != e_pos) {
		return false;
	}

	return true;
}

bool IsSeparator(char symbol) {
	if (symbol == '\n' || symbol == ' ') {
		return true;
	}

	return false;
}

void CheckNumbers(FILE* f) {
	int current_index = 0;
	int flag = 0;
	bool is_number = 0;

	while (!feof(f)) {
		char ch = fgetc(f);

		bool is_current_word = !IsSeparator(ch);
		while (is_number != is_current_word) {

			if (is_number) {
				int number_length = current_index - flag;
				fseek(f, flag, SEEK_SET);

				char* number = (char*) malloc(sizeof(char) * (number_length + 1));
				for (int i = 0; i < number_length; ++i) {
					number[i] = fgetc(f);
				}
				fgetc(f);
				number[number_length] = '\0';

				fprintf(stdout, "%s ", number);

				if (IsValidNumber(number)) {
					fprintf(stdout, "is legal.\n");
				} else {
					fprintf(stdout, "is illegal.\n");
				}

				free(number);
			}

			flag = current_index;
			is_number = is_current_word;
		}

		++current_index;
	}
}