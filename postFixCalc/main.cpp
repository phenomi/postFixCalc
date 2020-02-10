#include "Stack.h"
#include <string>

int main()

{
	Stack stored_numbers;
	int guided_prompts;
	string c;

	cout << "Do you want guided prompts to help with the calculator usage? (y/n): ";
	getline(cin, c);

	if (c == "y")
		guided_prompts = 1;
	else
		guided_prompts = 0;

	if (guided_prompts == 1) {
		stored_numbers.instructions();
		while (stored_numbers.do_command(stored_numbers.get_command(), stored_numbers));
	}

	int quit_program = 0; // variable to help control shutting down the program
	string user_input; // variable to hold the user's entered string
	string str_to_convert = ""; // placeholder variable to help with stof conversion
	float converted_float = 0; // placeholder variable to help with stof conversion
	int digit_counter; // variables to help the program correctly identify numbers 
	int skip_counter = 0; // that are bigger than single digits or float numbers

	if (guided_prompts == 0) {
		do {
			getline(cin, user_input);
			for (int i = 0; i < user_input.length(); i++) {
				user_input[i] = tolower(user_input[i]);
				if (user_input[i] == 'q') {
					quit_program = 1;
					break;
				}
				else if (user_input[i] == ' ' || skip_counter != 0) {
					if (skip_counter != 0) skip_counter--;
					continue;
				}
				else {
					if (isdigit(user_input[i])) {
						digit_counter = i + 1;
						skip_counter = 0;
						str_to_convert = user_input[i]; // saving first digit to the string we will convert
						while (digit_counter != -1) { // 
							if (isdigit(user_input[digit_counter]) || user_input[digit_counter] == '.') {
								str_to_convert += user_input[digit_counter];
								skip_counter++;
								digit_counter++;
							}
							else {
								converted_float = stof(str_to_convert);
								stored_numbers.push(converted_float);
								digit_counter = -1; // to get out of the loop
							}
						}
					}
				}
				if (user_input[i] == '=' || user_input[i] == '+' || user_input[i] == '-' || 
					user_input[i] == '*' || user_input[i] == '/' || user_input[i] == '%' || 
					user_input[i] == '^' || user_input[i] == 'v' || user_input[i] == 'a' || 
					user_input[i] == 's' || user_input[i] == 'x') {
					stored_numbers.do_command(user_input[i], stored_numbers);
				}

			}
		} while (quit_program != 1);
	}
}