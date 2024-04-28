

// Класс для управления таблицей полиномов, используя вектор для хранения.
class PolynomialArrayTable : public IPolynomialTable {
private:
    std::vector<std::pair<std::string, Polynomial>> table;  // Вектор, хранящий пары "имя-полином"
    std::string table_name = "PolynomialArrayTable";  // Имя таблицы для идентификации

public:
    // Метод для добавления полинома в таблицу
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        // Поиск существующего полинома по имени с помощью лямбда-функции
        auto it = std::find_if(table.begin(), table.end(), [&](const auto& item) {
            return item.first == name;
            });

        if (it != table.end()) {
            // Если найден, обновляем существующий полином
            it->second = polynomial;
        }
        else {
            // Если не найден, добавляем новую пару в конец вектора
            table.emplace_back(name, polynomial);
        }
    }

    // Метод для получения полинома по имени
    Polynomial& getPolynomial(const std::string& name) override {
        // Линейный поиск полинома по имени
        auto it = std::find_if(table.begin(), table.end(), [&](const auto& item) {
            return item.first == name;
            });

        if (it != table.end()) {
            // Если найден, возвращаем полином
            return it->second;
        }
        else {
            // Если не найден, бросаем исключение
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // Метод для удаления полинома по имени
    void removePolynomial(const std::string& name) override {
        // Поиск полинома для удаления
        auto it = std::find_if(table.begin(), table.end(), [&](const auto& item) {
            return item.first == name;
            });

        if (it != table.end()) {
            // Если найден, удаляем
            table.erase(it);
        }
        else {
            // Если не найден, бросаем исключение
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // Метод для получения имени таблицы
    std::string getTableName() const override {
        return table_name;
    }

    // Метод для печати содержимого таблицы
    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (const auto& entry : table) {
            os << entry.first << ": ";  // Вывод имени полинома
            entry.second.print(os);  // Вывод самого полинома
        }
        os << "-----------" << std::endl;
    }
};