bool Error::check()
{
	// Checking the first char
	if (math[0] == ')')
	{
		cout << "Expression can't start with a right bracket." << endl;
		return true;
	}
	else if (is_unary(math, 0) == false && is_operand(math[0]))
	{
		if (math[0] != '-')
		{
		cout << "Your expression starts with a binary operator." << endl;
		return true;
		}
	}
	else
	{
		//Checking the rest of the expression
		for (int i = 0; i < math.size() - 1; i++)
		{
			if ((is_operand(math[i]) && is_operand(math[i + 1])) && is_unary(math,i) == false)
			{
				cout << "Two binary operands in a row @ " << i << endl;
				return true;
			}
			if (is_unary(math,i) && is_operand(math[i+2]))
			{
				cout << "A unary operator cannot be followed by a binary operator. Error @ " << i << endl;
				return true;
			}
		}
	}
	return false;
}