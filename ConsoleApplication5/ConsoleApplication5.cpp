#include <iostream>

class Average {
private:
    std::int32_t m_value{ 0 };
    std::int32_t m_count{0};

public:
  Average() {}
  Average(const Average &other) = default;

  Average& operator+=(const Average &value) {
    ++m_count;
    m_value += value.m_value;
    return *this;
  }

  Average& operator+=(int val) {
    ++m_count;
    m_value += val;
    return *this;
  }
    
  friend std::ostream &operator<<(std::ostream &os, const Average &a) {
    if (a.m_count == 0) return os << 0;
    os << (static_cast<double>(a.m_value) / a.m_count);
    return os;
  }

};

int main() {
  
  Average avg{};
  std::cout << avg << '\n';

  avg += 4;
  std::cout << avg << '\n'; // 4 / 1 = 4

  avg += 8;
  std::cout << avg << '\n'; // (4 + 8) / 2 = 6

  avg += 24;
  std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

  avg += -10;
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

  (avg += 6) += 10;     // 2 calls chained together
  // выше появляется ошибка
  // сначала переменная вроде бы 6 и сумма 42
  // после выхода из выражения  m_count=5 m_value=32
  std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

  Average copy{avg};
  std::cout << copy << '\n';

  return 0;
}
