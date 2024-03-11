#include <map>

class Term {
public:
  // Сложение с другим термом
  void operator+=(const Term& other);
  // Умножение на другой терм
  void operator*=(const Term& other);
  // Дифференцирование терма
  void Differentiation();
  // Интегрирование терма
  void Integration();
private:
  // Коэффициент терма
  double coefficient;
  // Переменные и их степени
  std::map<char, int> variables;
};
