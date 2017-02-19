#include "state_machine.h"

void FormatToXML(FILE* output_stream, char* token_category, char* token_name, int number_of_line, int position, int length) {
	fprintf(output_stream, "\t<Token>\n");
	fprintf(output_stream, "\t\t<Category_of_token>%s</Category_of_token>\n", token_category);
	fprintf(output_stream, "\t\t<Name_of_token>%s</Name_of_token>\n", token_name);
	fprintf(output_stream, "\t\t<Number_of_line>%d</Number_of_line>\n", number_of_line);
	fprintf(output_stream, "\t\t<Position_in_line>%d</Position_in_line>\n", position);
	fprintf(output_stream, "\t\t<Length_name_of_token>%d</Length_name_of_token>\n", length);
	fprintf(output_stream, "\t</Token>\n");
}

bool IsKeyword(const char* word) {
	char* keywords[NUMBER_OF_KEYWORDS] = {
		"auto", "break", "case", "char", "const",
		"continue", "default", "do", "double",
		"else", "enum", "extern", "float", "for",
		"goto", "if", "inline", "int", "long",
		"register", "restrict", "return", "short",
		"signed", "sizeof", "static", "struct",
		"switch", "typedef", "union", "unsigned",
		"void", "volatile", "while", "_Bool",
		"_Complex", "_Imaginary", "bool"
	};

	for (int i = 0; i < NUMBER_OF_KEYWORDS; ++i) {

		if (strcmp(word, keywords[i]) == 0) {

			return true;
		}
	}

	return false;
}

bool IsOperator(const char* operator) {
	char* operators[NUMBER_OF_OPERATORS] = {
			"++", "--", "&", "*", "+", "-", "!", "/",
			"%", "<<", ">>", "<", ">", "<=", ">=", "==",
			"!=", "^", "&&", "||", "?", "=", "*=", "/=",
			"%=", "+=", "-=", "&=", "^=", "|="
	};

	for (int i = 0; i < NUMBER_OF_OPERATORS; ++i) {

		if (strcmp(operator, operators[i]) == 0) {

			return true;
		}
	}

	return false;
}

bool IsRightBracket(char ch) {
	return ch == ')' || ch == ']' || ch == '}';
}

bool IsLeftBracket(char ch) {
	return ch == '(' || ch == '[' || ch == '{';
}

state_t HighlightTokens(FILE* output_stream, CStack* line, state_t state, int number_of_line) {
	int current_position = 0;

	for (const char* s = line->base; s < line->base + size(line); ++s) {
		CStack* buffer = Constructor();

		if (s[0] == '\t') {
			current_position += 4;
		} else {
			++current_position;
		}

		switch (state) {

			case ST_USUAL:

				if (s[0] == '#' || line->base[0] == '\n' || (s[0] == '/' && s[1] == '/')) {
					return ST_USUAL;
				} else if (s[0] == '/' && s[1] == '*') {
					state = ST_MULTILINE_COMMENT;
					++s;
				}
				else {

					if (s[0] == '"') {
						state = ST_STRING_LITERAL;
						--current_position;
						--s;
					} else if (ispunct(s[0])) {
						state = ST_PUNCTUATOR;
						--current_position;
						--s;
					} else if (isdigit(s[0])) {
						state = ST_CONSTANT;
						--current_position;
						--s;
					} else if (isalpha(s[0])){
						state = ST_IDENTIFIER;
						--current_position;
						--s;
					}
				}

			case ST_MULTILINE_COMMENT:

				if (s[0] == '*' && s[1] == '/') {
					state = ST_USUAL;
					++s;

					continue;
				}

				break;

			case ST_STRING_LITERAL:

				while (true) {
					Push(buffer, s[0]);
					++s;

					if (s[0] == '"') {
						Push(buffer, s[0]);

						break;
					}
				}

				Push(buffer, '\0');
				FormatToXML(output_stream, "String literal", buffer->base, number_of_line, current_position, size(buffer) - 1);
				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;

			case ST_PUNCTUATOR:
				Push(buffer, s[0]);

				if (ispunct(s[1]) && !IsRightBracket(s[1]) && !IsLeftBracket(s[1]) && s[1] != ';' && s[1] != '"') {
					++s;
					Push(buffer, s[0]);
				}

				Push(buffer, '\0');

				if (IsRightBracket(buffer->base[0])) {
					FormatToXML(output_stream, "Closing bracket", buffer->base, number_of_line, current_position, size(buffer) - 1);
				} else if (IsLeftBracket(buffer->base[0])) {
					FormatToXML(output_stream, "Openning bracket", buffer->base, number_of_line, current_position, size(buffer) - 1);
				} else if (IsOperator(buffer->base)) {
					FormatToXML(output_stream, "Operator", buffer->base, number_of_line, current_position, size(buffer) - 1);
				} else {
					FormatToXML(output_stream, "Punctuator", buffer->base, number_of_line, current_position, size(buffer) - 1);
				}

				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;

			case ST_CONSTANT:
				Push(buffer, s[0]);
				Push(buffer, '\0');
				FormatToXML(output_stream, "Integer constant", buffer->base, number_of_line, current_position, 1);
				state = ST_USUAL;

				break;

			case ST_IDENTIFIER:

				while (true) {
					Push(buffer, s[0]);
					++s;

					if (isdigit(s[0]) || ispunct(s[0]) || isspace(s[0])) {
						--s;

						break;
					}
				}

				Push(buffer, '\0');
				bool is_keyword = IsKeyword(buffer->base);

				if (is_keyword) {
					FormatToXML(output_stream, "Keyword", buffer->base, number_of_line, current_position, size(buffer) - 1);
				} else {
					FormatToXML(output_stream, "Identifier", buffer->base, number_of_line, current_position, size(buffer) - 1);
				}

				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;
		}

		Destructor(buffer);
	}

	return state;
}

void GetLine(FILE* input_stream, CStack* buffer_string, int* index) {
	char buffer_char;

	while (true) {
		++(*index);
		buffer_char = fgetc(input_stream);
		Push(buffer_string, buffer_char);

		if (buffer_char == '\n') {
			Pop(buffer_string);

			break;
		}
	}
}

void ReadFromStream(FILE* input_stream, FILE* output_stream) {
	int current_index = 0;
	int current_line = 0;
	char buffer_char;
	state_t state = ST_USUAL;

	while (true) {
		buffer_char = fgetc(input_stream);
		++current_index;
		++current_line;

		if (buffer_char == EOF) {

			break;
		}

		fseek(input_stream, --current_index, SEEK_SET);

		CStack* buffer_string = Constructor();
		GetLine(input_stream, buffer_string, &current_index);

		state = HighlightTokens(output_stream ,buffer_string, state, current_line);
		Destructor(buffer_string);
	}
}