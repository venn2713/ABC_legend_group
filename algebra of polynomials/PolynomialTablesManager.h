#ifndef POLYNOMIAL_TABLES_MANAGER_H
#define POLYNOMIAL_TABLES_MANAGER_H

#include "Polynomial.h"
#include "PolynomialTable.h"
#include <memory>
#include <string>
#include <vector>
#include <map>

//  ласс дл€ управлени€ набором таблиц полиномов
class PolynomialTablesManager {
private:
  std::map<std::string, std::shared_ptr<PolynomialTable>> tables;

public:
  // –егистрирует новую таблицу в менеджере
  void registerTable(const std::string& tableName, std::shared_ptr<PolynomialTable> table) {
    tables[tableName] = table;
  }

  // ƒобавл€ет полином во все зарегистрированные таблицы
  void addPolynomialToAll(const Polynomial& poly) {
    for (auto& tablePair : tables) {
      tablePair.second->insert(poly);
    }
  }

  // ”дал€ет полином из всех зарегистрированных таблиц по имени полинома
  void removePolynomialFromAll(const std::string& polyName) {
    for (auto& tablePair : tables) {
      tablePair.second->remove(polyName);
    }
  }

  // »щет полином в указанной таблице по имени полинома
  std::shared_ptr<Polynomial> findPolynomialInTable(const std::string& tableName, const std::string& polyName) {
    if (tables.find(tableName) != tables.end()) {
      return tables[tableName]->find(polyName);
    }
    return nullptr; // ≈сли таблица не найдена, возвращаем nullptr
  }

  // ¬ыводит содержимое всех таблиц на экран
  void displayAll() const {
    for (const auto& tablePair : tables) {
      std::cout << "Table: " << tablePair.first << std::endl;
      tablePair.second->display();
    }
  }
};

#endif // POLYNOMIAL_TABLES_MANAGER_H
