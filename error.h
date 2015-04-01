#include <string>
#include <iostream>

using namespace std;

class Error
{
public:
	Error(string exp);
	bool check();

private:
	bool error_detected = false;
	string math;
};

Error::Error(string exp)
{
	math = exp;
}
