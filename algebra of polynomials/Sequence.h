#include <list>

template <typename T>
class Sequence {
public:
  // Вставка элемента в упорядоченную последовательность
  void insertInOrder(const T& value);
  // Удаление элемента из последовательности
  void erase(const T& value);
  // Доступ к элементу по индексу
  T operator;
private:
  // Данные, хранящиеся в последовательности
  std::list<T> data;
};
