#include <stack>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

//Function for power operation ^, because neither ** operator nor pow(base, power) method in math.h is working
int power(int base, int n){
	static int result = base;
	if (n == 1) 
		return result;
	else
		result *= base;
	    return power(base, n-1);
}
//Converts characters to strings
string convert_str(char ch){
	stringstream ss;
	string str;
	ss << ch;
	ss >> str;
	return str;
}

class Eval
{
public:
int eval(string math);
//It looks as though we need different types of operation functions
int int_operation(int rhs, int lhs, string op);
int int_operation(int the_int, string op); //Overloading function
bool comp_operation(int rhs, int lhs, string op);
bool bool_operation(bool rhs, bool lhs, string op);
bool bool_operation(bool the_bool, string op); //Overloading function
bool is_operand(const string ch);
bool is_int_operator(const string ch);
bool is_comp_operator(const string ch);
bool is_bool_operator(const string ch);
bool is_parenth(const string ch);
int precedence(const string op);

private:
stack<int> s_operand;
stack<string> s_operator;
static const string operands;
static const string int_operators;
static const string comp_operators;
static const string bool_operators;
};

const string Eval::operands = "0123456789";

const string Eval::int_operators = "+-*/%^++--";

const string Eval::comp_operators = "<>==<=>=";

const string Eval::bool_operators = "||&&!==";

int Eval::eval(string math)
{
	
	string op;
	int l_int, r_int;
	bool l_bool, r_bool;
	int int_result;
	bool bool_result;
    for(int i=0; i<math.size(); i++){
        string math_str = convert_str(math[i]);
        if(is_operand(math_str) || math_str == "(")  //NOTE 1
	        s_operand.push(stoi(math_str));//stoi converts a string to an integer
        else if(math_str == ")" || precedence(math_str) < precedence(s_operator.top())){
	        while(precedence(math_str) <= precedence(s_operator.top())){
				op = s_operator.top();
				s_operator.pop();
				if (op == "++" || op == "--" || op == "!"){ //Pop off only 1 operand
					if (op == "++" || op == "--"){//Perform int operation with 1 operand
						string str = convert_str(s_operand.top());
						if (!is_parenth(str)){
						    r_int = static_cast<int>(s_operand.top());
						    int_result = int_operation(r_int, op);
						}
					    s_operand.pop();
					}
					else{ // Perform ! operation with 1 operand
						r_bool = static_cast<bool>(s_operand.top()); //FIX: It could be one whole expression as well
					    s_operand.pop();
						bool_result = bool_operation(r_bool, op);
					}
				}
				if (is_int_operator(op)){ //Operator is for 2 ints, returns int
					l_int = static_cast<int>(s_operand.top());
					s_operand.pop();
					r_int = static_cast<int>(s_operand.top());
					s_operand.pop();
                    int_result = int_operation(r_int, l_int, op);
				    s_operand.push(int_result);
				}
				else if (is_comp_operator(op)){//Operator is for 2 ints, returns bool
					l_int = static_cast<int>(s_operand.top());
					s_operand.pop();
					r_int = static_cast<int>(s_operand.top());
					s_operand.pop();
					bool_result = comp_operation(r_int, l_int, op);
					s_operand.push(bool_result);
				}
				else if (is_bool_operator(op)){//Operator is for 2 bools, returns bool
					l_bool = static_cast<bool>(s_operand.top()); 
					s_operand.pop();
					r_bool = static_cast<bool>(s_operand.top());
					s_operand.pop();
					bool_result = bool_operation(r_bool, l_bool, op);
				    s_operand.push(bool_result);
				}
			}
	    }
        else //The operator has higher precedence than the one on top of the stack
	        s_operator.push(math_str);
    }
}
//See if the char is an open parenthesis - used for discarding open parentheses
bool Eval::is_parenth(const string ch){
	if (ch == "(")
		return true;
	else
		return false;
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
		return lhs < rhs;
	else if (op == "<=")
		return lhs <= rhs;
	else if (op == ">=")
		return lhs >= rhs; 
	else if (op == "==")
		return rhs == lhs;
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

//Precendence value for each operator
int precedence(const string op){
	if (op == "!" || op == "++" || op == "--" || op == "-")
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


/* NOTE 1

I was thinking would it be easier to just use recursion to deal with parenthesis?
Create a new string of the inside of the parenthesis and send it in its own eval function.

Just something to think about....

*/