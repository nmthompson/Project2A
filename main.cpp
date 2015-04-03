#pragma once
#include <iostream>
#include "evaluator.h"

int main(){
	Eval eval;
	string result = eval.evaluate("7+9");
	cout << result << endl;
	system("pause");
	return 0;
}