#include "evaluator.h"
#include "error.h"
int main(){
	Eval eval;
	string result = "7+9";
	Error error(result);
	eval.evaluate(result);
	cout << result << endl;
	system("pause");
	return 0;
}