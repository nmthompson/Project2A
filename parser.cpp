#include "parser.h"

char Parser::parse_Exp(string exp){ //Handles parsing the string and passing tokens to eval class for evaluation

	for (int i = 0; i < exp.size(); i++)
	{
		
	}
	return exp[i];
}
bool Parser::parse_ErrorCheck(){ //Checks for all errors that could occur while parsing



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