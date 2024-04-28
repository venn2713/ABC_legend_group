

class PolynomialHashTable : public IPolynomialTable {
private:
    struct Entry {
        std::string key;
        Polynomial value;
        bool occupied;

        Entry() : occupied(false) {}
    };

    std::vector<Entry> table;
    std::string table_name = "PolynomialHashTable";

    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char c : key) {
            hash_value += static_cast<size_t>(c);
        }
        return hash_value % table.size();
    }

public:
    PolynomialHashTable(size_t size = 100) : table(size) {}

    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        size_t index = hash(name);
        while (table[index].occupied) {
            index = (index + 1) % table.size();
        }
        table[index].key = name;
        table[index].value = polynomial;
        table[index].occupied = true;
    }

    Polynomial& getPolynomial(const std::string& name) override {
        size_t index = hash(name);
        while (table[index].occupied && table[index].key != name) {
            index = (index + 1) % table.size();
        }
        if (!table[index].occupied || table[index].key != name) {
            throw std::out_of_range("Polynomial not found");
        }
        return table[index].value;
    }

    void removePolynomial(const std::string& name) override {
        size_t index = hash(name);
        while (table[index].occupied && table[index].key != name) {
            index = (index + 1) % table.size();
        }
        if (table[index].occupied && table[index].key == name) {
            table[index].occupied = false;
        }
    }

    std::string getTableName() const override {
        return table_name;
    }

    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (const auto& entry : table) {
            if (entry.occupied) {
                os << entry.key << ": ";
                entry.value.print(os);
            }
        }
        os << "-----------" << std::endl;
    }
};
