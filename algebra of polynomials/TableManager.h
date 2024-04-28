#include "Polinomial.h"
#include "IPolynomialTable.h"
#include "ListTable.h"
#include "ArrayTable.h"
#include "OrderedTable.h"
#include "RBTreeTable.h"
#include "HachTable.h"
#include "ChainedlHashTable.h"

// Класс для управления множеством таблиц полиномов
class TableManager {
private:
    std::vector<IPolynomialTable*> tables;  // Вектор указателей на таблицы полиномов
    IPolynomialTable* activeTable = nullptr;  // Указатель на текущую активную таблицу

public:
    // Конструктор
    TableManager() {
        // Создание и добавление таблиц в вектор управления
        tables.push_back(new PolynomialListTable());
        tables.push_back(new PolynomialArrayTable());
        tables.push_back(new PolynomialOrderedTable());
        tables.push_back(new PolynomialTableWithRedBlackTree());
        tables.push_back(new PolynomialHashTable());
        tables.push_back(new ChainedPolynomialHashTable());

        // Установка первой таблицы в списке как активной
        setActiveTable(tables[0]);  // Установка активной таблицы по умолчанию
    }

    // Деструктор
    ~TableManager() {
        // Очистка памяти: удаление всех таблиц
        for (auto& table : tables) {
            delete table;  // Удаление объектов, на которые указывают указатели
        }
    }

    // Установка активной таблицы по указателю
    void setActiveTable(IPolynomialTable* table) {
        activeTable = table;
    }

    // Установка активной таблицы по имени
    void setActiveTableByName(const std::string& name) {
        for (auto& table : tables) {
            if (table->getTableName() == name) {
                activeTable = table;
                return;
            }
        }
        std::cout << "Table not found with the name: " << name << std::endl;
    }

    // Добавление полинома во все таблицы
    void addPolynomialToAllTables(const std::string& name, const Polynomial& polynomial) {
        for (auto& table : tables) {
            table->addPolynomial(name, polynomial);
        }
    }

    // Удаление полинома из всех таблиц
    void removePolynomialFromAllTables(const std::string& name) {
        for (auto& table : tables) {
            table->removePolynomial(name);
        }
    }

    // Получение активной таблицы
    IPolynomialTable* getActiveTable() const {
        return activeTable;
    }

    // Вывод содержимого активной таблицы
    void printActiveTable() const {
        if (activeTable) {
            std::cout << *activeTable;
        }
    }
};