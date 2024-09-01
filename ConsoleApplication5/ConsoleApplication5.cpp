/*
12.15 — std::optional
https ://www.learncpp.com/cpp-tutorial/stdoptional/
*/

#include <iostream>

// The reciprocal of x is 1/x, returns 0.0 if x=0
double reciprocal(double x)
{
	if (x == 0.0)
		return 0.0;

	return 1.0 / x;
}

void testReciprocal(double d)
{
	double result{ reciprocal(d) };
	std::cout << "The reciprocal of " << d << " is ";
	if (result != 0.0)
		std::cout << result << '\n';
	else
		std::cout << "undefined\n";
}

int main()
{
	testReciprocal(5.0);
	testReciprocal(-4.0);
	testReciprocal(0.0);

	return 0;
}