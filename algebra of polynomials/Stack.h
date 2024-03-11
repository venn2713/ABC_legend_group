#include <list>

template <typename T>
class Stack {
public:
  // Добавление элемента в стек
  void push(const T& value);
  // Удаление элемента из стека
  void pop();
  // Получение верхнего элемента стека
  T getTop();
  // Проверка стека на пустоту
  bool empty();
private:
  // Данные, хранящиеся в стеке
  std::list<T> data;
};
