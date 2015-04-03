#include "parser.h"
#include "evaluator.h"

int parse_Exp(string exp){ //Handles parsing the string and passing tokens to eval class for evaluation
	//begin parse loop
	parse_ErrorCheck(); //call to error check in parse loop

	//as parsing, calls eval class to handle logic, which also does error checks
	Eval eval;
	eval.evaluate(exp);
	//end parse loop

	return 0;
}
bool parse_ErrorCheck(){ //Checks for all errors that could occur while parsing




	return false;
}

bool Parser::closing_paren(string exp)
{
	int open = 0;
	int close = 0;

	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '(')
			open++;
		else if (exp[i] == ')')
			close++;
	}
	if (open == close)
		return true;
	else
		return false;
}