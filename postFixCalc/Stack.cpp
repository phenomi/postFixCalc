#include "Stack.h"

Stack::Stack()
/*
Pre:  None.
Post: The stack is initialized to be empty.
*/
{
	count = 0;
}

bool Stack::empty() const
/*
Pre:  None.
Post: If the Stack is empty, true is returned.
	  Otherwise false is returned.
*/

{
	bool outcome = true;
	if (count > 0) outcome = false;
	return outcome;
}

bool Stack::full(Stack &s) const
{
	bool outcome = true;
	if (s.count == maxstack)
		outcome = false;
	return outcome;
}

void Stack::clear(Stack & s)
{
	while (!s.empty()) {
		s.pop();
	}
}

void Stack::delete_all(Stack & s, Stack_entry x)
{
	Stack temporaryStack;
	Stack_entry temporaryVar;

	while (!s.empty()) {
		s.top(temporaryVar);
		if (temporaryVar != x) {
			temporaryStack.push(temporaryVar);
		}
		s.pop();
	}
	
	while (!temporaryStack.empty()) {
		temporaryStack.top(temporaryVar);
		s.push(temporaryVar);
		temporaryStack.pop();
	}
}

int Stack::size(Stack & s) const
{
	return count;
}

void Stack::instructions()
{
	cout << endl
		<< "This program allows the user to enter decimal numbers" << endl
		<< "followed by an operator [+] [-] [*] [/] [%] [^] [v]" << endl
		<< "For example, if the command [S] is entered, then" << endl
		<< "the program will calculate the sum of the numbers." << endl
		<< endl

		<< "The valid commands are:" << endl
		<< "[?] - Push numbers to stack" << endl
		<< "[=] - Print the top of the stack" << endl
		<< "[+] [-] [*] [/] [%] [^] [v] are arithmetic operations" << endl
		<< "[A] - Calculate the average of the numbers in the stack" << endl
		<< "[S] - Calculate the sum of the numbers in the stack" << endl
		<< "[X] - Exchange the numbers in the stack between each other" << endl
		<< "[H] - This help screen" << endl
		<< "[Q] - Quit" << endl << endl;

	return;
}

char Stack::get_command()
{
		char command;
		bool waiting = true;
		cout << "Select command and press <Enter>:";

		while (waiting) {
			cin >> command;
			command = tolower(command);
			if (command == '?' || command == '=' || command == '+' ||
				command == '-' || command == '*' || command == '/' ||
				command == 'a' || command == 's' || command == 'x' ||
				command == 'h' || command == 'q') waiting = false;

			else {
				cout << "Please enter a valid command:" << endl
					<< "Press [H] for the help screen,"
					<< "or alternatively [Q]uit." << endl;
			}
		}
		return command;
}

bool Stack::do_command(char command, Stack & numbers)
{
		/*
		Pre:  The first parameter specifies a valid calculator command.
		Post: The command specified by the first parameter
			  has been applied to the Stack of numbers given by the second parameter.
			  A result of true is returned unless command == 'q'.
		Uses: The class Stack.
		*/

		Stack_entry p, q;
		Stack_entry temp_var_1, temp_var_2;
		Stack_entry sum = 0;
		int counter_var = 0;
		float operand1 = 0;  // variables to help with the subtraction function
		float operand2 = 0;

		switch (command) {
		case '?':
			cout << "Enter a real number: " << flush;
			cin >> p;
			if (numbers.push(p) == overflow)
				cout << "Warning: Stack full, lost number" << endl;
			break;

		case '=':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else
				cout << p << endl;
			break;

		case '+':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
					numbers.push(p);
				}

				else {
					numbers.pop();
					if (numbers.push(q + p) == overflow)
						cout << "Warning: Stack full, lost result" << endl;
				}
			}
			break;
		case '-':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.pop_top(numbers, operand2);
			numbers.pop_top(numbers, operand1);
			numbers.push(operand1 - operand2);
			break;

		case '*':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.pop_top(numbers, operand2);
			numbers.pop_top(numbers, operand1);
			numbers.push(operand1 * operand2);
			break;

		case '/':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.pop_top(numbers, operand2);
			numbers.pop_top(numbers, operand1);
			numbers.push(operand1 / operand2);
			break;

		case '%':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.pop_top(numbers, operand2);
			numbers.pop_top(numbers, operand1);
			numbers.push(fmod(operand1, operand2));
			break;

		case '^':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.pop_top(numbers, operand2);
			numbers.pop_top(numbers, operand1);
			numbers.push(pow(operand1, operand2));
			break;

		case 'v':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else
				numbers.push(sqrt(p));
			break;

		case 'x':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			numbers.top(temp_var_1);
			numbers.pop();
			numbers.top(temp_var_2);
			numbers.pop();
			numbers.push(temp_var_1);
			numbers.push(temp_var_2);
			break;

		case 's':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			while (!numbers.empty()) {
				numbers.pop_top(numbers, p);
				sum += p;
			}
			numbers.push(sum);
			break;

		case 'a':
			if (numbers.top(p) == underflow)
				cout << "Stack empty" << endl;
			else {
				numbers.pop();
				if (numbers.top(q) == underflow) {
					cout << "Stack has just one entry" << endl;
				}
			}
			numbers.push(p);

			while (!numbers.empty()) {
				numbers.pop_top(numbers, p);
				sum += p;
				counter_var++;
			}
			numbers.push(sum / counter_var);
			break;

		case 'h':
			instructions();
			break;

		case 'q':
			cout << "Calculation finished.\n";
			return false;
		}
		return true;
	}

Error_code Stack::pop()
/*
Pre:  None.
Post: If the Stack is not empty, the top of
	  the Stack is removed.  If the Stack
	  is empty, an Error_code of underflow is returned.
*/

{
	Error_code outcome = success;
	if (count == 0)
		outcome = underflow;
	else count--;
	return outcome;
}

Error_code Stack::top(Stack_entry &item) const
/*
Pre:  None.
Post: If the Stack is not empty, the top of
	  the Stack is returned in item.  If the Stack
	  is empty an Error_code of underflow is returned.
*/

{
	Error_code outcome = success;
	if (count == 0)
		outcome = underflow;
	else
		item = entry[count - 1];
	return outcome;
}

Error_code Stack::push(const Stack_entry &item)
/*
Pre:  None.
Post: If the Stack is not full, item is added to the top
	  of the Stack.  If the Stack is full,
	  an Error_code of overflow is returned and the Stack is left unchanged.
*/

{
	Error_code outcome = success;
	if (count >= maxstack)
		outcome = overflow;
	else
		entry[count++] = item;
	return outcome;
}

Error_code Stack::copy_stack(Stack &dest, Stack &source)
{
	Stack temporaryStack;
	Stack_entry temporaryVar;

	while (!source.empty()) {
		source.top(temporaryVar);
		temporaryStack.push(temporaryVar);
		source.pop();
	}
	while (!temporaryStack.empty()) {
		temporaryStack.top(temporaryVar);
		dest.push(temporaryVar);
		source.push(temporaryVar);
		temporaryStack.pop();
	}

	Error_code outcome = success;
	if (count >= maxstack)
		outcome = overflow;
	else if (count == 0)
		outcome = underflow;
	return outcome;
}

Error_code Stack::pop_top(Stack & s, Stack_entry & t)
{
	Error_code outcome = success;

	// take top value, insert into variable 't', and remove value from stack
	s.top(t);
	s.pop();

	if (s.count == 0)
		outcome = underflow;
	return outcome;
}
