#include <algorithm> // std::max std::copy_n
#include <iostream>

class MyString
{
private:
    char* m_data{};
    int m_length{};

public:
    MyString(const char* data = nullptr, int length = 0)
        : m_length{ std::max(length, 0) }
    {
        if (length)
        {
            m_data = new char[static_cast<std::size_t>(length)];
            std::copy_n(data, length, m_data);
        }
    }
    ~MyString()
    {
        delete[] m_data;
    }

    MyString(const MyString&) = default;

    MyString& operator=(const MyString& str);


    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    friend void swap(MyString& Lh, MyString& Rh);
};

int main()
{
    MyString alex("Alexey", 7);
    std::cout << alex << std::endl;
    MyString employee;
    employee = alex;
    std::cout << employee << '\n';

    std::cin.get();
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_data;
    return out;
}

void swap(MyString& Lh, MyString& Rh)
{
    using std::swap;
    swap(Lh.m_data, Rh.m_data);
    swap(Lh.m_length, Rh.m_length);
}

MyString& MyString::operator=(const MyString& str)
{
    MyString temp{ str };

    swap(*this, temp);
    return *this;
}
