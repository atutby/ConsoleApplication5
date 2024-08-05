#include <algorithm> // std::copy
#include <cassert> // assert()
#include <initializer_list> // std::initializer_list
#include <iostream> 

class IntArray
{
private:
	int m_length{};
	int* m_data{};

public:
	IntArray() = default;

	IntArray(int length)
		: m_length{ length }
		, m_data{ new int[static_cast<std::size_t>(length)] {} }
	{

	}

	IntArray(std::initializer_list<int> list)
		// allow IntArray to be initialized via list initalization
		: IntArray(static_cast<int>(list.size()))
		// use delegating constructor to set up initial array
	{
		// Now initialize our array from the list
		std::copy(list.begin(), list.end(), m_data);
	}

	~IntArray()
	{
		delete[] m_data;
	}

	IntArray(const IntArray&) = delete; // to avoid shallow copies
	IntArray& operator=(const IntArray& list) = delete;
	// to avoid shallow copies

	IntArray& operator=(std::initializer_list<int> list)
	{
		IntArray temp{ list };
		swap(*this, temp);

		return *this;
	}

	void swap(IntArray& first, IntArray& second)
	{
		using std::swap;
		swap(first.m_length, second.m_length);
		swap(first.m_data, second.m_data);
	}


	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int main()
{
#ifdef first
	IntArray array{};
	array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement

	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' '; // undefined behavior
#endif

#ifndef first
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	std::cout << '\n';

	array = { 1, 3, 5, 7, 9, 11 };

	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	std::cout << '\n';
#endif

	return 0;
}


/*
*
23.7 — std::initializer_list
https://www.learncpp.com/cpp-tutorial/stdinitializer_list/
*/