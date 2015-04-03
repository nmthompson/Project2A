#include <string>
#include <iostream>

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
