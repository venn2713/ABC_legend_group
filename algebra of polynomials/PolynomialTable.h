#ifndef POLYNOMIAL_TABLE_H
#define POLYNOMIAL_TABLE_H

#include "Polynomial.h"
#include <memory>
#include <string>
#include <vector>

// Абстрактный базовый класс для таблицы полиномов
class PolynomialTable {
public:
    // Виртуальный деструктор для корректного удаления производных объектов
    virtual ~PolynomialTable() {}

    // Добавление полинома в таблицу
    // Если полином с таким именем уже существует, он будет заменен
    virtual void insert(const Polynomial& polynomial) = 0;

    // Удаление полинома из таблицы по его имени
    // Возвращает true, если полином был успешно удален
    virtual bool remove(const std::string& name) = 0;

    // Поиск полинома по имени
    // Возвращает указатель на полином или nullptr, если полином не найден
    virtual std::shared_ptr<Polynomial> find(const std::string& name) const = 0;

    // Вывод содержимого таблицы на экран
    virtual void display() const = 0;

    // Получение всех имен полиномов в таблице
    // Возвращает вектор строк с именами полиномов
    virtual std::vector<std::string> getNames() const = 0;

    // Новые методы для батчевого добавления и удаления
    virtual void insertBatch(const std::vector<Polynomial>& polynomials) = 0;
    virtual void removeBatch(const std::vector<std::string>& names) = 0;
};

#endif // POLYNOMIAL_TABLE_H
