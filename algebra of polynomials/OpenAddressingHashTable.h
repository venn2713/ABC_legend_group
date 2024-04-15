#ifndef OPENADDRESSINGHASHTABLE_H
#define OPENADDRESSINGHASHTABLE_H



class OpenAddressingHashTable : public AbstractTable {
private:
    struct TTableRec 
    {
        string key;
        TList<Monom> value;
    };

    static const size_t tableSize = 100;
    vector<TTableRec> data{ tableSize };

    size_t hashFunction(const string& key) const {

        size_t hash = 0;
        for (char c : key) 
        {
            hash += static_cast<size_t>(c);
        }
        return hash % tableSize;
    }

public:
    OpenAddressingHashTable() = default;

    OpenAddressingHashTable(const OpenAddressingHashTable& other) {

        for (const auto& rec : other.data) 
        {
            insert(rec.key, rec.value);
        }
    }

    OpenAddressingHashTable& operator=(const OpenAddressingHashTable& other) {

        if (this != &other) 
        {
            clear();
            for (const auto& rec : other.data) 
            {
                insert(rec.key, rec.value);
            }
        }
        return *this;
    }

    size_t size() const noexcept override {

        size_t count = 0;
        for (const auto& rec : data) 
        {
            if (!rec.key.empty())
            {
                count++;
            }
        }
        return count;
    }

    TList<Monom>& operator[](size_t pos) override {

        throw logic_error("Not implemented");
    }

    void deleteData(string key) override {

        size_t index = hashFunction(key);
        size_t startIndex = index;
        do {
            if (data[index].key == key)
            {
                data[index].key.clear();
                return;
            }
            index = (index + 1) % tableSize;
        } 
        while (index != startIndex && !data[index].key.empty());
    }

    TList<Monom>* find(string key) override {

        size_t index = hashFunction(key);
        size_t startIndex = index;
        do {
            if (data[index].key == key) 
            {
                return &(data[index].value);
            }
            index = (index + 1) % tableSize;
        } 
        while (index != startIndex && !data[index].key.empty());
        return nullptr;
    }

    void insert(string key, TList<Monom> value) override {

        size_t index = hashFunction(key);
        size_t startIndex = index;
        do {
            if (data[index].key.empty()) 
            {
                data[index].key = key;
                data[index].value = value;
                return;
            }
            index = (index + 1) % tableSize;
        } 
        while (index != startIndex);
    }

    void changeKey(string key, string newKey) override {

        TList<Monom>* value = find(key);
        if (value)
        {
            insert(newKey, *value);
            deleteData(key);
        }
    }

    ostream& print(ostream& stream, string name) const override {
        for (const auto& rec : data) 
        {
            if (rec.key == name) 
            {
                stream << "Key: " << rec.key << ", Value: " << rec.value << endl;
            }
        }
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const OpenAddressingHashTable& table) {

        table.print(stream, activeName);
    }

    void clear() {

        for (auto& rec : data) 
        {
            rec.key.clear();
        }
    }
};

#endif