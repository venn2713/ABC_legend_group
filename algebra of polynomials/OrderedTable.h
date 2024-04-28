

// Класс для управления таблицей полиномов, используя упорядоченный вектор для хранения.
class PolynomialOrderedTable : public IPolynomialTable {
private:
    std::vector<std::pair<std::string, Polynomial>> table;  // Вектор, хранящий пары "имя-полином", упорядоченные по имени
    std::string table_name = "PolynomialOrderedTable";  // Имя таблицы

public:
    // Добавление полинома в таблицу
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        // Используем std::lower_bound для нахождения точки вставки или обновления полинома
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // Обновляем существующий полином
            it->second = polynomial;
        }
        else {
            // Вставляем новый полином на найденное место
            table.insert(it, { name, polynomial });
        }
    }

    // Получение полинома по имени
    Polynomial& getPolynomial(const std::string& name) override {
        // Поиск полинома с использованием std::lower_bound
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // Возвращаем найденный полином
            return it->second;
        }
        else {
            // Если полином не найден, бросаем исключение
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // Удаление полинома по имени
    void removePolynomial(const std::string& name) override {
        // Аналогичный поиск полинома для удаления
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // Удаление полинома, если найден
            table.erase(it);
        }
        else {
            // Если не найден, бросаем исключение
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // Получение имени таблицы
    std::string getTableName() const override {
        return table_name;
    }

    // Печать содержимого таблицы
    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (const auto& entry : table) {
            os << entry.first << ": ";  // Вывод имени полинома
            entry.second.print(os);  // Вывод самого полинома
        }
        os << "-----------" << std::endl;
    }
};