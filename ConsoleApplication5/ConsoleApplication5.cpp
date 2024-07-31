#include <algorithm>
#include <iostream>
#include <cassert> // for assert

class IntArray
{
private: 
	int m_length{ 0 };
	int* m_array{ nullptr };

public:
	explicit IntArray(int length)
		: m_length{ length }
	{
		assert(length > 0 && "IntArray length should be a positive integer");

		m_array = new int[m_length] {};
	}

	// Copy constructor that does a deep copy
	IntArray(const IntArray& array)
		: m_length{ array.m_length }
	{
		// Allocate a new array
		m_array = new int[m_length] {};
		
		// Copy elements from original array to new array
		std::copy_n(array.m_array, m_length, m_array);
	}

	~IntArray()
	{
		delete[] m_array;
	}

	// If you're getting crazy values here you propbably forgot to do a deep copy
	// in your constructor
	friend std::ostream& operator<<(std::ostream& out, const IntArray& array)
	{
		for (int count{ 0 }; count < array.m_length; ++count)
		{
			out << array.m_array[count] << ' ';
		}
		return out;
	}

	int& operator[] (const int index)
	{
		assert(index >= 0);
		assert(index < m_length);
		return m_array[index];
	}

	// Asignment operator that does a deep copy
	IntArray& operator= (IntArray array)
	{
		swap(*this, array);
		return *this;
	}

	friend void swap(IntArray& first, IntArray& second)
	{
		using std::swap;
		swap(first.m_length, second.m_length);
		swap(first.m_array, second.m_array);
	}

};

IntArray fillArray()
{
	IntArray a(5);
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}


int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a };
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}


/*

Операторы преобразовани¤ типов
https://metanit.com/cpp/tutorial/5.15.php

13.11 Перегрузка операторов преобразовани¤ типов данных
https://radioprog.ru/post/1247

21.11 Overloading typecasts
https://www.learncpp.com/cpp-tutorial/overloading-typecasts/

21.12 Overloading the assignment operator
https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/

*/