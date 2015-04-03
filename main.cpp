#pragma once
#include <iostream>
#include "evaluator.h"

int main(){
	Eval eval;
	string result = eval.evaluate("7+9");
	std::cout << result;
	system("pause");
	return 0;
}