#ifndef ORDERED_ARRAY_POLYNOMIAL_TABLE_H
#define ORDERED_ARRAY_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>

// Конкретная реализация таблицы полиномов на основе упорядоченного динамического массива
class OrderedArrayPolynomialTable : public PolynomialTable {
private:
    // Структура для хранения полинома с его именем
    struct NamedPolynomial {
        std::string name;
        std::shared_ptr<Polynomial> polynomial;

        NamedPolynomial(const std::string& name, std::shared_ptr<Polynomial> polynomial)
            : name(name), polynomial(polynomial) {}

        // Оператор сравнения для упорядочивания по имени
        bool operator<(const NamedPolynomial& other) const {
            return name < other.name;
        }
    };

    std::vector<NamedPolynomial> table; // Упорядоченный вектор именованных полиномов

public:
    // Деструктор
    virtual ~OrderedArrayPolynomialTable() override {}

    // Вставка полинома в таблицу
    void insert(const Polynomial& polynomial) override {
        NamedPolynomial newEntry(polynomial.getName(), std::make_shared<Polynomial>(polynomial));
        auto it = std::lower_bound(table.begin(), table.end(), newEntry);
        if (it != table.end() && it->name == polynomial.getName()) {
            // Если полином с таким именем уже существует, заменяем его
            *it = newEntry;
        } else {
            // Иначе вставляем полином в упорядоченный массив
            table.insert(it, newEntry);
        }
    }

    // Удаление полинома из таблицы
    bool remove(const std::string& name) override {
        auto it = std::find_if(table.begin(), table.end(),
                               [&](const NamedPolynomial& item) { return item.name == name; });
        if (it != table.end()) {
            table.erase(it);
            return true;
        }
        return false;
    }

    // Поиск полинома по имени
    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        auto it = std::lower_bound(table.begin(), table.end(), NamedPolynomial(name, nullptr),
                                   [](const NamedPolynomial& item, const NamedPolynomial& val) { return item.name < val.name; });
        if (it != table.end() && it->name == name) {
            return it->polynomial;
        }
        return nullptr;
    }

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& item : table) {
            std::cout << "Name: " << item.name << ", Polynomial: " << *(item.polynomial) << std::endl;
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        std::transform(table.begin(), table.end(), std::back_inserter(names),
                       [](const NamedPolynomial& item) { return item.name; });
        return names;
    }

    // Батчевое добавление
    void insertBatch(const std::vector<Polynomial>& polynomials) override {
      for (const auto& polynomial : polynomials) {
        insert(polynomial);
      }
    }

    // Батчевое удаление
    void removeBatch(const std::vector<std::string>& names) override {
      for (const auto& name : names) {
        remove(name);
      }
    }
};

#endif // ORDERED_ARRAY_POLYNOMIAL_TABLE_H
