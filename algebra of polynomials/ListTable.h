class PolynomialListTable : public IPolynomialTable {
private:
    std::string table_name = "PolynomialListTable";
    std::list<std::pair<std::string, Polynomial>> table;

public:
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        // ѕровер€ем, существует ли уже полином с таким именем
        auto it = std::find_if(table.begin(), table.end(),
            [&](const auto& entry) { return entry.first == name; });

        // ≈сли полином с таким именем уже есть, замен€ем его
        if (it != table.end()) {
            it->second = polynomial;
        }
        else { // »наче добавл€ем новый полином в конец списка
            table.emplace_back(name, polynomial);
        }
    }

    Polynomial& getPolynomial(const std::string& name) override {
        // »щем полином по имени и возвращаем его
        auto it = std::find_if(table.begin(), table.end(),
            [&](const auto& entry) { return entry.first == name; });

        if (it != table.end()) {
            return it->second;
        }
        else {
            throw std::out_of_range("Polynomial not found");
        }
    }

    void removePolynomial(const std::string& name) override {
        // ”дал€ем полином по имени, если он есть
        table.remove_if([&](const auto& entry) { return entry.first == name; });
    }

    std::string getTableName() const override {
        return table_name;
    }

    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (const auto& entry : table) {
            os << entry.first << ": ";
            entry.second.print(os);
        }
        os << "-----------" << std::endl;
    }
};
