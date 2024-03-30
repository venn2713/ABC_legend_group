#ifndef CHAINED_HASH_POLYNOMIAL_TABLE_H
#define CHAINED_HASH_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <vector>
#include <list>
#include <functional>
#include <memory>
#include <iostream>

// Реализация хеш-таблицы с методом цепочек для полиномов
class ChainedHashPolynomialTable : public PolynomialTable {
private:
    struct HashEntry {
        std::string name;
        std::shared_ptr<Polynomial> polynomial;

        HashEntry(const std::string& name, std::shared_ptr<Polynomial> polynomial)
            : name(name), polynomial(polynomial) {}
    };

    std::vector<std::list<HashEntry>> table;
    size_t tableSize;

    // Простая хеш-функция для демонстрации
    size_t hashFunction(const std::string& key) const {
        std::hash<std::string> hasher;
        return hasher(key) % tableSize;
    }

public:
    explicit ChainedHashPolynomialTable(size_t size = 101) : tableSize(size), table(size) {}

    // Вставка полинома в таблицу
    void insert(const Polynomial& polynomial) override {
        size_t index = hashFunction(polynomial.getName());
        auto& bucket = table[index];
        for (auto& entry : bucket) {
            if (entry.name == polynomial.getName()) {
                entry.polynomial = std::make_shared<Polynomial>(polynomial); // Update existing
                return;
            }
        }
        bucket.emplace_back(polynomial.getName(), std::make_shared<Polynomial>(polynomial)); // Add new
    }

    // Удаление полинома из таблицы
    bool remove(const std::string& name) override {
        size_t index = hashFunction(name);
        auto& bucket = table[index];
        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const HashEntry& entry) {
            return entry.name == name;
        });
        if (it != bucket.end()) {
            bucket.erase(it);
            return true;
        }
        return false;
    }

    // Поиск полинома по имени
    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        size_t index = hashFunction(name);
        const auto& bucket = table[index];
        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const HashEntry& entry) {
            return entry.name == name;
        });
        if (it != bucket.end()) {
            return it->polynomial;
        }
        return nullptr;
    }

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                std::cout << "Name: " << entry.name << ", Polynomial: " << *(entry.polynomial) << std::endl;
            }
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                names.push_back(entry.name);
            }
        }
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

#endif // CHAINED_HASH_POLYNOMIAL_TABLE_H
