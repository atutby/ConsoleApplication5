// Putting it all together
// https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
// 9.5 — std::cin and handling invalid input

#include <cstdlib> // for std::exit
#include <iostream>
#include <limits>

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false othewise
bool clearFailedExtraction()
{
	// Check for failed extraction
	if (!std::cin) // If the previous extraction failed
	{
		if (std::cin.eof())
		{
			exit(0);
		}

		std::cin.clear();
		ignoreLine();

		return true;
	}

	return false;
}

double getDouble()
{
	while (true) // Loop until user enters a valid input
	{
		std::cout << "Enter a decimal number: ";
		double x{};
		std::cin >> x;

		if (clearFailedExtraction())
		{
			std::cout << "Oops, that input is invalid. Please try again.\n";
			continue;
		}

		ignoreLine();
		return x;
	}
}

char getOperator()
{
	while (true) //
	{
		std::cout << "Enter one of the following: +, -, *, or /: ";
		char operation{};
		std::cin >> operation;

		if (!clearFailedExtraction())
			ignoreLine();

		switch (operation)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			return operation;
		default: // 
			std::cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
}

void printResult(double x, char operation, double y)
{
	std::cout << x << ' ' << operation << ' ' << y << " is ";

	switch (operation)
	{
	case '+':
		std::cout << x + y << '\n';
		return;
	case '-':
		std::cout << x - y << '\n';
		return;
	case '*':
		std::cout << x * y << '\n';
		return;
	case '/':
		if (y == 0.0)
			break;

		std::cout << x / y << '\n';
		return;
	}

	std::cout << "???";
}

int main()
{
	while (true)
	{

		double x{ getDouble() };
		char operation{ getOperator() };
		double y{ getDouble() };

		// Handle division by 0
		while (operation == '/' && y == 0.0)
		{
			std::cout << "The denominator cannot be zero. Try again.\n";
			y = getDouble();
		}

		printResult(x, operation, y);
		std::cout << '\n';

	}

	return 0;
}