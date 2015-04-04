#include "evaluator.h"

bool Error::check(string math) 
{
	istringstream tokens(math);
	char next;
	char temp;
	char temp2;
	int char_num = 1;
	tokens >> next;
	// Checking the first char(s)
	if (!(is_operand(convert_str(next))) && (!(next == '+' || next == '-') && !((char)tokens.peek() == next) || next != '!')){ 
		//Invalid beginning char error
        cout << "Expression starts with an invalid character." << endl;
		system("pause");
	    exit(1);
	}
	else{
		tokens.putback(next);
		//Checking the rest of the expression
		while (tokens >> next)
		{
			temp = (char)tokens.peek();
	        /*if ((is_operand(convert_str(next)) && is_operand(convert_str(temp)) && is_unary(math, i) == false){
					cout << "Two binary operands in a row"<< endl;
					return true;
			}
			if (is_unary(math, i) && is_operand(math[i + 2])){
					cout << "A unary operator cannot be followed by a binary operator. " << endl;
					return true;
			}*/
			if (next == '/' && temp == '0'){ //Division by 0
				cout << "Division by 0 error @ char " << char_num << endl;
				system("pause");
			    exit(1);
			}
		char_num++;
		}
	}
	return false;
}