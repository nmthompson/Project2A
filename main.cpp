#pragma once

#include "evaluator.h"
#include "parser.h"

int main(){
	Eval eval;
	Parser parse;
	int result = parse.parse_Exp("7-5>=2&&6*5<=30");

	return 0;
}