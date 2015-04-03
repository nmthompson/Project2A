#include <sstream>
#include <iostream>
#include "evaluator.h"
#include "error.h"

//Function for power operation ^, because neither ** operator nor pow(base, power) method in math.h is working
int power(int base, int n){
	static int result = base;
	if (n == 1) 
		return result;
	else
		result *= base;
	    return power(base, n-1);
}
//Converts ints or chars to strings
template<class T>
string convert_str(T ch){
	stringstream ss;
	string s;
	ss << ch;
	ss >> s;
	return s;
}
//Converts strings to bools
bool convert_bool(string str){
	if (str == "true")
		return true;
	else if (str == "false")
		return false;
}
//Converts string ints to bools
string bool_str(char integer){
	if (integer == '1')
		return "true";
	else if (integer == '0')
		return "false";
}

const string Eval::operands = "(0123456789truefalse";

const string Eval::int_operators = "+-*/%^++--";

const string Eval::comp_operators = "<>==<=>=";

const string Eval::bool_operators = "||&&!==";

string Eval::evaluate(const string& math){ //All spaces should be removed from the string beforehand (in exception handler func)
	string result;
	string math_str;
	char next;
	char temp;
	istringstream tokens(math);
    while (tokens >> next){
		//Check for operators with 2 chars
		if (next == '0' || next == '1'){ //Possible boolean int  
			if ((char)tokens.peek() == '&' || (char)tokens.peek() == '=' || (char)tokens.peek() == '|') //If bool operator indicated at right
		        math_str = bool_str(next);
			else if (!s_operator.empty() &&  is_bool_operator(s_operator.top())) //If bool operator indicated at left
				math_str = bool_str(next);
		}
	    //Check for operators with 2 chars
		if (tokens >> temp){ //next can't be the last char in expression
			tokens.putback(temp);
			if (!(isdigit(next)) && (next == (char)tokens.peek() || next == '>' && (char)tokens.peek() == '=' 
				|| next == '<' && (char)tokens.peek() == '=' || next == '!' && (char)tokens.peek() == '=')){
				math_str = next; 
				tokens >> next; //Now next is the peek char
				math_str += convert_str(next);
			}
			else
				math_str = convert_str(next);
		}
		else
            math_str = convert_str(next);

        if (is_operand(math_str)){ //If operand is a digit, there may be more digits to add to it
			if (isdigit(next)){
				bool dig_read = true;
				while (dig_read){ //While digits are being read 
				    if (tokens >> temp && isdigit(temp)){//If there are more digits of the integer to be read
					    math_str += temp; //Add next digit to math_str
				    }
					else{
						tokens.putback(temp);
						dig_read = false;
					}
				}
			}
	        s_operand.push(math_str);
		}

		else if (math_str == ")"){ //Closing parenthesis means operation(s) inside parentheses can be performed  
			while (s_operand.top() != "(" && !s_operator.empty())
				eval_op(result);
		}
		else if (!s_operator.empty()){ //Make sure there is an operator in the stack to compare to
			if (precedence(math_str) >= precedence(s_operator.top()))
			    s_operator.push(math_str);
			else{
	            while(!s_operator.empty() && precedence(math_str) < precedence(s_operator.top()))
				    eval_op(result); 
				s_operator.push(math_str);
	        }
		}
        else //operator stack empty
	        s_operator.push(math_str);
	}
	//No characters left to read - finish any leftover operations
	while (!s_operator.empty() && !s_operand.empty())
		eval_op(result);
	result = s_operand.top();
	s_operand.pop();//Pop result - an open parentheses might be left on the stack 
	return result;
}

//See whether "true" or "false" is the result, push onto stack and return
string Eval::tf_push(bool what){
	if (what){
	    s_operand.push("true");
	    return "true";
	}
	else{
		s_operand.push("false");
	    return "false";
	}
}

//See if the char is a numerical operand
bool Eval::is_operand(const string ch){
	return operands.find(ch) != string::npos;
}

//See if the char is a numerical operator
bool Eval::is_int_operator(const string ch){
	return int_operators.find(ch) != string::npos;
}

//See if the char is a comparative operator
bool Eval::is_comp_operator(const string ch){
	return comp_operators.find(ch) != string::npos;
}

//See if the char is a boolean operator
bool Eval::is_bool_operator(const string ch){
	return bool_operators.find(ch) != string::npos;
}

//Evaluate an integer operation
int Eval::int_operation(int rhs, int lhs, string op){
	if (op == "+")
        return lhs + rhs;
	else if (op == "-")
		return lhs - rhs;
	else if (op == "*")
		return lhs * rhs;
	else if (op == "/")
		return static_cast<int>(lhs / rhs);
	else if (op == "%")
		return lhs % rhs;
	else if (op == "^")
		return power(lhs, rhs);
}

//Overloaded int_operation
int Eval::int_operation(int rhs, string op){
	if (op == "++")
		return ++rhs;
	else if (op == "--")
		return --rhs;
}

//Evaluate a boolean operation with comparators 
bool Eval::comp_operation(int rhs, int lhs, string op){
	if (op == "<")
		return lhs < rhs;
	else if (op == ">")
		return lhs > rhs;
	else if (op == "<=")
		return lhs <= rhs;
	else if (op == ">=")
		return lhs >= rhs; 
	else if (op == "==")
		return rhs == lhs;
	else if (op == "!=")
		return rhs != lhs;
}

//Evaluate a boolean expression with bools
bool Eval::bool_operation(bool rhs, bool lhs, string op){
	if (op == "||")
		return rhs || lhs;
	else if (op == "&&")
		return rhs && lhs;
	else if (op == "==")
		return rhs == lhs;
}

//Overloaded bool_operation
bool Eval::bool_operation(bool rhs, string op){
	return !rhs;
}

void Eval::pop_paren(){ //Used for clearing out open parenth stuck between operands or at end 
	if (s_operand.top() == "(")
		s_operand.pop();
	else
		return;
}

//Precendence value for each operator
int Eval::precedence(const string op){
	if (op == "!" || op == "++" || op == "--")
		return 8;
	else if (op == "^")
		return 7;
	else if (op == "*" || op == "/" || op == "%")
		return 6;
	else if (op == "+" || op == "-") // Need to deal with the minus symbol, whether it has 8 or 5 prec
		return 5;
	else if (op == ">" || op == ">=" || op == "<" || op == "<=")
		return 4;
	else if (op == "&&")
		return 2;
	else if (op == "||")
		return 1;
}

void Eval::eval_op(string result){ //Inside the main while loops of eval
	string op;
	int l_int, r_int;
	bool l_bool, r_bool;
	op = s_operator.top();
	s_operator.pop();
    if (op == "++" || op == "--" || op == "!"){ //Pop off only 1 operand
	    if (op == "++" || op == "--"){//Perform int operation with 1 operand
		    r_int = stoi(s_operand.top());
			s_operand.pop();
		    result = convert_str(int_operation(r_int, op));
			s_operand.push(result); 
		}
		else{ // Perform ! operation with 1 operand
		    if (s_operand.top() == "true")
			    r_bool = true;
				else{
				    r_bool = false;
					s_operand.pop();
				    result = tf_push(bool_operation(r_bool, op));
				}
		}
	}
	else if (is_int_operator(op)){ //Operator is for 2 ints, returns int
	    r_int = stoi(s_operand.top());
		s_operand.pop();
		pop_paren(); //Danger, open parenth might be here, needs to be popped
		l_int = stoi(s_operand.top());
		s_operand.pop();
		result = convert_str(int_operation(r_int, l_int, op)); 
		s_operand.push(result);
	}
	else if (is_comp_operator(op)){//Operator is for 2 ints, returns bool
	    r_int = stoi(s_operand.top());
		s_operand.pop();
		pop_paren();
		l_int = stoi(s_operand.top());
		s_operand.pop();
		result = tf_push(comp_operation(r_int, l_int, op));
	}
	else if (is_bool_operator(op)){//Operator is for 2 bools, returns bool
	    r_bool = convert_bool(s_operand.top()); 
		s_operand.pop();
		pop_paren();
		l_bool = convert_bool(s_operand.top());
		s_operand.pop();
		result = tf_push(bool_operation(r_bool, l_bool, op));
	}
}