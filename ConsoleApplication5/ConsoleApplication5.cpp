#include <cassert>
#include <iostream>
#include <algorithm> // std::copy
#include <cstddef> // std::size_t

class dumb_array
{
public:
    // 
    dumb_array(std::size_t size = 0)
        : mSize(size),
        mArray(mSize ? new int[mSize]() : nullptr)
    {}

    // 
    dumb_array(const dumb_array& other)
        : mSize(other.mSize),
        mArray(mSize ? new int[mSize] : nullptr)
    {
        std::copy(other.mArray, other.mArray + mSize, mArray);
    }

    ~dumb_array()
    {
        delete[] mArray;
    }

    dumb_array& operator=(const dumb_array& other)
    {
        if (this != &other)
        {
            // избавл¤емс¤ от старых данных...
            delete[] mArray; // (2)
            mArray = nullptr; // (2) (i)

            mSize = other.mSize; // (3)
            mArray = mSize ? new int[mSize] : nullptr; // (3)
        }

        return *this;
    }

    dumb_array& operator=(dumb_array other) // (1)
    {
        swap(*this, other); // (2)

        return *this;
    }

    dumb_array(dumb_array&& other) noexcept // (1)
        : dumb_array() // 
    {
        swap(*this, other);
    }

    friend void swap(dumb_array& first, dumb_array& second) // nothrow
    {
        // 
        using std::swap;

        //
        //
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

private:
    std::size_t mSize;
    int* mArray;
};

/*
MyString
std::copy_n(str.m_data, m_length, m_data); // str.m_data -> m_data
std::max
<algorithm>
MyString& <- return *this;
operator<<
char* m_data{}
int m_length{}
new char[static_cast<std::size_t>(length)];
nullptr
*/

namespace mystring {

    class MyString
    {
    private:
        char* m_data{};
        size_t m_length{};

    public:
        static int count;


    public:
        MyString(const char* data = nullptr, int length = 0)
            : m_length{ 0 }
        {
            std::cout << "ctor\n";
            if (length)
            {
                m_data = new char[length];
                std::copy_n(data, length, m_data); // copy length elements of data into m_data
            }
        }

        ~MyString()
        {
            ++count;
            std::cout << "dctor " << count << '\n';
            delete[] m_data;
        }

        MyString(const MyString& str) // some complilers (gcc) warn if have pointer members but no declared copy constructor
        {

            if (str.m_length)
            {
                m_length = str.m_length;
                m_data = new char[m_length];
                std::copy_n(str.m_data, m_length, m_data);
            }
        }


        // Overloaded assignment
        //MyString& operator=(const MyString& str)
        //{
        //    std::cout << "operator=(const MyString& str)\n";
        //    if (this == &str)
        //        return *this;

        //    // if data exists in the current string, delete it
        //    if (m_data) delete[] m_data;

        //    m_length = str.m_length;
        //    m_data = nullptr;

        //    if (m_length)
        //        m_data = new char[static_cast<std::size_t>(str.m_length)];

        //    std::copy_n(str.m_data, m_length, m_data); // copies m_length elements of str.m_data into m_data


        //    // return the existing object so we can chain this operator
        //    return *this;
        //}


        MyString& operator=(const MyString& str)
        {
            std::cout << "operator=(const sMyString& str)\n";
            MyString temp{ str };
            swap(*this, temp);
            return *this;
        }

        //MyString(MyString&& str) noexcept
        //    : MyString()
        //{
        //    std::cout << "MyString(MyString&& str) noexcept\n";
        //    swap(*this, str);
        //}

        friend std::ostream& operator<<(std::ostream& out, const MyString& s);

        static friend void swap(MyString& first, MyString& second) // nothrow
        {
            std::cout << "swap\n";
            using std::swap;
            swap(first.m_data, second.m_data);
            swap(first.m_length, second.m_length);
        }
    };


    std::ostream& operator<<(std::ostream& out, const MyString& s)
    {
        return out << s.m_data;
    }

    int MyString::count = 0;


}



int main() {
    using namespace mystring;

    MyString alex("Alex", 5); // Meet Alex
    std::cout << "alex__________\n";
    MyString employee;
    std::cout << "employee_________\n";
    employee = alex; // Alex is our newest employee
    std::cout << "employee = alex___________\n";
    std::cout << employee << '\n'; // Say your name, employee
    std::cout << "print employee name________\n";
    alex = alex; // Alex is himself
    std::cout << "alex = alex_________\n";


    system("pause");
    std::cin.get();
    return 0;
}

/*

ќператоры преобразовани¤ типов
https://metanit.com/cpp/tutorial/5.15.php

13.11 Ц ѕерегрузка операторов преобразовани¤ типов данных
https://radioprog.ru/post/1247

21.11 Ч Overloading typecasts
https://www.learncpp.com/cpp-tutorial/overloading-typecasts/

21.12 Ч Overloading the assignment operator
https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/


*/






