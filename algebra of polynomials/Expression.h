#include "Sequence.h"
#include "Term.h"

class Expression {
public:
  // Сложение с другим выражением
  void operator+=(const Expression& other);
  // Умножение на другое выражение
  void operator*=(const Expression& other);
  // Дифференцирование выражения
  void Differentiation();
  // Интегрирование выражения
  void Integration();
private:
  // Термы, составляющие выражение
  Sequence<Term> terms;
};
