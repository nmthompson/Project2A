<<<<<<< HEAD
=======
#include "error.h"

const string operands = "(0123456789";
bool Error::is_operand(char ch){
	return operands.find(ch) != string::npos;
}
bool Error::is_unary(string math, int i)
{
	if (math[i] == math[i + 1])
		return true;
	else
		return false;
}

bool Error::check(string math)
{
	// Checking the first char
	if (math[0] == ')')
	{
		cout << "Expression can't start with a right bracket." << endl;
		return true;
	}
	else if ((is_unary(math, 0) == false && is_operand(math[0])) && math[0] != '-') //Element 0 allowed operators: '(' '-' "++" "--"
	{
		cout << "Your expression starts with a binary operator." << endl;
		return true;
	}
	else
	{
		//Checking the rest of the expression
		for (int i = 0; i < math.size() - 1; i++)
		{
			if (math[i] != ' ') //Skip spaces.
			{

				if ((is_operand(math[i]) && is_operand(math[i + 1])) && is_unary(math, i) == false)
				{
					cout << "Two binary operands in a row @ " << i << endl;
					return true;
				}
				if (is_unary(math, i) && is_operand(math[i + 2]))
				{
					cout << "A unary operator cannot be followed by a binary operator. Error @ " << i << endl;
					return true;
				}

			}
		}
	}
	return false;
}
>>>>>>> d0e839a072cac8c21f7b8cfda33ea92de02b3293
