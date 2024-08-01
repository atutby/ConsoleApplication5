#include <cassert>
#include <cstdint>
#include <iostream>

class FixedPoint2
{
private:
	std::int16_t m_base{};
	std::int8_t m_decimal{};

public:
	FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
		: m_base{ base }, m_decimal{ decimal }
	{
		// If either (or both) of the non-fractional and fractional part
		if (m_base < 0 || m_decimal < 0)
		{
			// Make sure base is negative
			if (m_base > 0)
				m_base = -m_base;
			// Make sure decimal is negative
			if (m_decimal > 0)
				m_decimal = -m_decimal;		
		}
	}

	explicit operator double() const
	{
		return m_base + (static_cast<double>(m_decimal) / 100);
	}
};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
{
	out << static_cast<double>(fp);
		return out;
}

int main()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';
	std::cout << static_cast<double>(a) << '\n';
	assert(static_cast<double>(a) == 34.56);

	FixedPoint2 b{ -2, 8 };
	assert(static_cast<double>(b) == -2.08);

	FixedPoint2 c{ 2, -8 };
	assert(static_cast<double>(c) == -2.08);

	FixedPoint2 d{ -2, -8 };
	assert(static_cast<double>(d) == -2.08);

	FixedPoint2 e{ 0, -5 };
	assert(static_cast<double>(e) == -0.05);

	FixedPoint2 f{ 0, 10 };
	assert(static_cast<double>(f) == 0.1);

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