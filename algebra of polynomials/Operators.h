#include <string>

template <typename T>
class Operators {
public:
  // Проверка, является ли строка операцией
  bool IfIsOperation(const std::string& str);
  // Получение приоритета операции
  int GetPriority(const std::string& operation);
  // Выполнение операции над элементами
  T Calculation(const T& left, const T& right, const std::string& operation);
};
