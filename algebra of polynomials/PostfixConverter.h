#include "Operators.h"
#include "Stack.h"
#include <string>

class PostfixConverter {
public:
  // Преобразование инфиксного выражения в постфиксное
  std::string ToPostfix(const std::string& infix);
  // Проверка корректности выражения
  bool CheckOfExpression(const std::string& expression);
  // Вычисление постфиксного выражения
  double Calculate(const std::string& postfix);
private:
  // Операторы, используемые в выражении
  Operators<double> operators;
  // Стек для хранения операций при преобразовании выражений
  Stack<std::string> stack;
};
