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
        cout << "Expression starts with an invalid character" << endl;
		system("pause");
	    exit(1);
	}
	else{
		tokens.putback(next);
		//Checking the rest of the expression
		while (tokens >> next)
		{
			temp = (char)tokens.peek();
	        if ((next == '&' || next == '|' || next == '=') && (temp != next)){
				cout << "This isn't a valid operator" << endl;
			    system("pause");
				exit(1);
			}
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