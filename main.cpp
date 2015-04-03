#pragma once

#include "parser.h"

int main(){
	Parser parse;
	int result = parse.parse_Exp("7-5>=2&&6*5<=30");

	return 0;
}