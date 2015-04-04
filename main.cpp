#include "evaluator.h"

int main(){
	Eval eval;
	cout << eval.evaluate("1/0") << endl; 
	system("pause");
	return 0;
}