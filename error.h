#include <string>
#include <iostream>

using namespace std;

class Error
{
public:
	Error(string exp);
	bool check(string math);

private:
	string math;
};

Error::Error(string exp)
{
	math = exp;
}
