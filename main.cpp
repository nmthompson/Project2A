#pragma once

#include "evaluator.h"

int main(){
	Eval eval;
	int result = eval.evaluate("7-5>=2&&6*5<=30");

	return 0;
}