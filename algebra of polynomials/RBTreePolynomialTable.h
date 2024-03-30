#ifndef RBTREE_POLYNOMIAL_TABLE_H
#define RBTREE_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <map>
#include <memory>
#include <string>

// Реализация таблицы полиномов на основе красно-черного дерева
class RBTreePolynomialTable : public PolynomialTable {
private:
    // Используем std::map для хранения полиномов, ключом будет имя полинома
    std::map<std::string, std::shared_ptr<Polynomial>> table;

public:
    // Вставка полинома в таблицу
    void insert(const Polynomial& polynomial) override {
        table[polynomial.getName()] = std::make_shared<Polynomial>(polynomial);
    }

    // Удаление полинома из таблицы по имени
    bool remove(const std::string& name) override {
        auto it = table.find(name);
        if (it != table.end()) {
            table.erase(it);
            return true;
        }
        return false;
    }

    // Поиск полинома по имени
    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        auto it = table.find(name);
        if (it != table.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& pair : table) {
            std::cout << "Name: " << pair.first << ", Polynomial: " << *(pair.second) << std::endl;
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        for (const auto& pair : table) {
            names.push_back(pair.first);
        }
        return names;
    }
};

#endif // RBTREE_POLYNOMIAL_TABLE_H