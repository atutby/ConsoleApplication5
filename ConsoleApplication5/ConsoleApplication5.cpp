/*
12.15 — std::optional
https://www.learncpp.com/cpp-tutorial/stdoptional/

std::optional<T>
https://metanit.com/cpp/tutorial/10.3.php

C++ Weekly - Ep 421 - You're Using optional, variant, pair, tuple, any, and expected Wrong!
https://www.youtube.com/watch?v=0yJk5yfdih0
https://compiler-explorer.com/z/h1joah85P
*/


#ifdef a1

#include <iostream>
#include <optional>
// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
	if (y == 0)
		return {};
	return x / y;
}



int main()
{
	std::optional<int> result1{ doIntDivision(21, 5) };
	if (result1)
		std::cout << "Result 1: " << *result1 << '\n';
	else
		std::cout << "Result 1: failed\n";

	std::optional<int> result2{ doIntDivision(5, 0) };

	if (result2)
	{
		std::cout << "Result 2: " << *result2 << '\n';
	}
	else
		std::cout << "Result 2: failed\n";


	return 0;
}
#endif



#ifdef a4pointerVersion
#include <string>

struct Employee
{
	std::string name{};
	int id;
};

void printEmployeeID(const Employee* e = nullptr)
{
	if (e)
	{
		std::cout << "Your ID number is " << e->id << ".\n";
	}
	else
		std::cout << "Your ID number is not known.\n";
}

int main()
{
	printEmployeeID();

	Employee e{ "James", 34 };
	printEmployeeID(&e);

	return 0;
}

#endif

#ifdef a5overloading
#include <string>

struct Employee
{
	std::string name{};
	int id;
};

void printEmployeeID()
{
	std::cout << "Your ID number is not known.\n";
}

void printEmployeeID(const Employee& e)
{
	std::cout << "Your ID number is " << e.id << ".\n";
}

int main()
{
	printEmployeeID();

	Employee e{ "James", 34 };
	printEmployeeID(e); // we know the Employee's ID now

	printEmployeeID({ "Dave", 62 }); // we can even pass rvalues

	return 0;
}
#endif



#ifdef met1
/*
 https://metanit.com/cpp/tutorial/10.3.php
 std::optional<T>
 Последнее обновление : 07.03.2023
*/
#include <string>
#include <optional>

std::optional<unsigned> find_index(const std::string&, char);
void print_index(std::optional<unsigned>, char);

int main()
{
	const std::string text = "An apple a day keep the doctor away.";

	// 
	char p_char{'p'};
	const std::optional<unsigned> p_index{ find_index(text, p_char) };
	print_index(p_index, p_char);

	//
	char b_char{ 'b' };
	const std::optional<unsigned> b_index{ find_index(text, b_char) };
	print_index(b_index, b_char);
}

void print_index(std::optional<unsigned> index, char c)
{
	if (index)
		std::cout << "Index of " << c << ": " << *index << std::endl;
	else
		std::cout << "Index of " << c << " not found" << std::endl;
}

std::optional<unsigned> find_index(const std::string& text, char c)
{
	if (text.empty())
		return std::nullopt;
	for (unsigned i{}; i < text.size(); i++)
	{
		if (text[i] == c)
		{
			return i;
		}
	}

	return std::nullopt;
}

#endif



#ifdef y1weekly
//C++ Weekly - Ep 421 - You're Using optional, variant, pair, tuple, any, and expected Wrong!
//https://www.youtube.com/watch?v=0yJk5yfdih0

#include <cstdio>
#include <source_location>
#include <optional>
#include <expected>
#include <string_view>

void print(const std::source_location& location = std::source_location::current()) noexcept
{
	std::puts(location.function_name());
}

struct Lifetime {
	explicit Lifetime(int) noexcept { print(); }
	Lifetime() noexcept { print(); }
	Lifetime(Lifetime &&) noexcept { print(); }
	Lifetime(const Lifetime &) noexcept { print(); }
	~Lifetime() noexcept { print(); }
	Lifetime& operator=(const Lifetime&) noexcept { print(); return *this; }
	Lifetime& operator=(Lifetime&&) noexcept { print(); return *this; }
};

//std::optional<Lifetime> get_value()
std::expected<Lifetime, std::string_view> get_value()
{
	//std::optional<Lifetime> retval;
	//retval = Lifetime{ 42 };
	//Lifetime mylifetime{ 42 };
	//retval = mylifetime;
	//return retval;
	//return Lifetime{ 42 };

	//std::optional<Lifetime> l;
	//l.emplace(42);
	//return l;

	//return std::optional<Lifetime>{42};

	//return Lifetime{ 42 };

	//return { 42 };

	//return std::optional<Lifetime>{ 42 };

	//return std::optional<Lifetime>{std::in_place_t{}, 42 }; // work for optional

	//return {std::in_place_t{}, 42 };


	Lifetime l{ 42 };
	//std::expected<Lifetime, std::string_view> l{ 42 };
	// do other work
	//return l;
	//return Lifetime{ 42 };
	//return std::expected<Lifetime, std::string_view>{ 42 };
	return l;
}

int main()
{
	get_value();
}

#endif



#ifdef a0doIntDivision

#include <iostream>
#include <optional> // for std::optional (C++17)
#define print(val) printValue(val, #val)

std::optional<int> doIntDivision(int x, int y);
void printValue(std::optional<int> op, const char *name);

int main()
{
	std::optional<int> result1{ doIntDivision(20, 5) };
	print(result1);

	std::optional<int> result2{ doIntDivision(5, 0) };
	print(result2);

	return 0;
}


std::optional<int> doIntDivision(int x, int y)
{
	if (y == 0)
		return {};
	return x / y;
}

void printValue(std::optional<int> op, const char *name)
{
	if (op) // if the function returned a value
		std::cout << name << ": " << *op << '\n'; // get the value
	else
		std::cout << name << ": failed\n";
}

#endif



#ifdef get-variable-name
//https://www.codeproject.com/Questions/5283867/Cplusplus-get-variable-name

#define printValue( val ) print( val, # val )

void print(int num, const char* name)
{
	std::cout << name << ": {" << num << "}" << std::endl;
}

int main()
{
	int mynum;
	std::cout << "enter number->" << std::endl;
	std::cin >> mynum;
	printValue(mynum);
}

#endif



#ifdef function-overloading-super

#include <iostream>
#include <string>

struct Employee
{
	std::string name{}; // expensive to copy
	int id;
};

void printEmployeeID()
{
	std::cout << "Your ID number is not known.\n";
}

void printEmployeeID(const Employee& e)
{
	std::cout << "Your ID number is " << e.id << ".\n";
}

int main()
{
	printEmployeeID();

	Employee e{ "James", 34 };
	printEmployeeID(e); // we know the Employee's ID now

	printEmployeeID({ "Dave", 62 });

	return 0;
}

#endif



#ifdef itself
#include <limits>

std::optional<double> func(int a, int b)
{
	if (b)
	{
		double result{ 1.0 * a / b };
		std::cout << " 1.0 * " << a << " / " << b  << " = " << result << '\n';
		return result;
	}

	std::cout << "Division by zero don't know.\n";
	return std::nullopt;
}

int main()
{
	func(5, 0);
	func(5, 2);

	std::cout << "std::numeric_limits<int>::lowest() = " << std::numeric_limits<int>::lowest() << '\n';
	std::cout << "std::numeric_limits<int>::max() = " << std::numeric_limits<int>::max() << '\n';
	std::cout << "sizeof(int) = " << sizeof(int) << '\n';
	std::cout << "sizeof(bool) = " << sizeof(bool) << '\n';
	std::cout << "sizeof(char) = " << sizeof(char) << '\n';
	std::cout << "sizeof(double) = " << sizeof(double) << '\n';
	std::cout << "sizeof(float) = " << sizeof(float) << '\n';
	std::cout << "sizeof(unsigned long) = " << sizeof(unsigned long) << '\n';
	std::cout << "sizeof(long long) = " << sizeof(long long) << '\n';


}
#endif



#ifdef reciprocal
#include <iostream>

// The reciprocal of x is 1/x, returns 0.0 if x=0
double reciprocal(double x)
{
	if (x == 0.0) // if x is semantically invalid
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
	double arr[]{ 5.0, -4.0, 0.0 };
	for (auto elem : arr)
	{
		testReciprocal(elem);
	}

}
#endif



#ifdef reciprocal_my
#include <iostream>
#include <optional>

std::optional<double> reciprocal(double x)
{
	if (x == 0.0)
		return {};

	return 1.0 / x;
}

int main()
{
	double arr[]{ 5.5, -4.0, 0.0, 0.2, 0.25 };
	std::optional<double> result{};
	for (auto elem : arr)
	{
		result = reciprocal(elem);
	if (result)
		std::cout << "Reciprocal of " << elem << ": " << *result << '\n';
	else
		std::cout << "Reciprocal of " << elem << ": " << "failed\n";
	}

}

#endif


#ifdef find_index
#include <iostream>
#include <string>
#include <optional>

std::optional<unsigned> find_index(const std::string&, char);
void print_index(std::optional<unsigned>, char);

int main()
{
	const std::string text = "An apple a day keep the doctor away.";
	char p_char{ 'p' };
	const std::optional<unsigned> p_index{ find_index(text, p_char) };
	print_index(p_index, p_char);

	char b_char{ 'b' };
	const std::optional<unsigned> b_index{ find_index(text, b_char) };
	print_index(b_index, b_char);
}


void print_index(std::optional<unsigned> index, char c)
{
	if (index)
		std::cout << "Index of " << c << ": " << *index << std::endl;
	else
		std::cout << "Index of " << c << " not found" << std::endl;
}

std::optional<unsigned> find_index(const std::string& text, char c)
{
	if (text.empty())
		return std::nullopt;
	for (unsigned i{}; i < text.size(); i++)
	{
		if (text[i] == c)
			return i;
	}
	return std::nullopt;
}
#endif



#ifdef pow
//https://metanit.com/cpp/tutorial/10.3.php
#include <iostream>
#include <optional>

double pow(double, std::optional<unsigned> = std::nullopt);
int main()
{
	double n1 = pow(4, 3);
	std::cout << n1 << std::endl;
	double n2 = pow(4);
	std::cout << n2 << std::endl;
}


double pow(double number, std::optional<unsigned> exp)
{
	unsigned a = exp.value_or(2);
	double result{ 1.0 };
	for (unsigned i{}; i < a; i++)
	{
		result *= number;
	}
	return result;
}
#endif



#ifndef chapter-12-summary-and-quiz_Questaion#5
//https://www.learncpp.com/cpp-tutorial/chapter-12-summary-and-quiz/
#include <algorithm> // for std::swap
#include <iostream>

void sort2(int& lesser, int& greater)
{
	// If the values are already sorted, we have nothing to do
	if (lesser <= greater)
		return;

	std::swap(lesser, greater);
}


int main()
{
	int x{7};
	int y{ 5 };

	std::cout << x << ' ' << y << '\n';

	sort2(x, y);
	std::cout << x << ' ' << y << '\n';

	sort2(x, y);
	std::cout << x << ' ' << y << '\n';

	return 0;
}
#endif // !chapter-12-summary-and-quiz_Questaion#5
