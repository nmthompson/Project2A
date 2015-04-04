#pragma once
#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <iostream>

using namespace std;

class Eval
{
public:
string evaluate(const string& math);
//It looks as though we need different types of operation functions
int int_operation(int rhs, int lhs, string op);
int int_operation(int the_int, string op); //Overloading function
bool comp_operation(int rhs, int lhs, string op);
bool bool_operation(bool rhs, bool lhs, string op);
bool bool_operation(bool the_bool, string op); //Overloading function
bool is_operand(const string ch);
bool is_bool_operand(const string str);
bool is_int_operator(const string ch);
bool is_comp_operator(const string ch);
bool is_bool_operator(const string ch);
void tf_push(bool what);
int precedence(const string op);
void pop_paren();
void eval_op(string result);
//Converts ints or chars to strings
template<class T>
string convert_str(T ch);

protected:
stack<string> s_operand; //Every operand as a string is more convenient - no need for a bool and an int stack
stack<string> s_operator; //Same goes for operators, since some of them have more than 1 char
static const string operands;
static const string bool_operands;
static const string int_operators;
static const string comp_operators;
static const string bool_operators;
};

class Error : public Eval
{
public:
	Error(string exp){ math = exp;} 
	bool check(string math); //This function calls the functions below to check for errors
	//bool is_unary(string& math, int index);

private:
	string math;
};
