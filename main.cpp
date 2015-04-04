<<<<<<< HEAD
#pragma once

#include "parser.h"

int main(){
	Parser parse;
	int result = parse.parse_Exp("7-5>=2&&6*5<=30");

=======
#include "evaluator.h"
#include "error.h"
int main(){
	Eval eval;
	string result = "7+9";
	Error error(result);
	eval.evaluate(result);
	cout << result << endl;
	system("pause");
>>>>>>> d0e839a072cac8c21f7b8cfda33ea92de02b3293
	return 0;
}