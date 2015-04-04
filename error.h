<<<<<<< HEAD
=======
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Error
{
public:
	Error(string exp);
	bool check(string math);
	bool is_operand(char x);
	bool is_unary(string x, int i);
private:
	string math;
};

Error::Error(string exp)
{
	math = exp;
}
>>>>>>> d0e839a072cac8c21f7b8cfda33ea92de02b3293
