#ifndef CHAINEDHASHTABLE_H
#define CHAINEDHASHTABLE_H


class ChainedHashTable : public AbstractTable {
private:
    struct TTableRec {
        string key;
        TList<Monom> value;
    };

    static const size_t tableSize = 100;
    vector<TList<TTableRec>> data{ tableSize };

    size_t hashFunction(const string& key) const {

        size_t hash = 0;
        for (char c : key) {
            hash += static_cast<size_t>(c);
        }
        return hash % tableSize;
    }

public:
    ChainedHashTable() = default;

    ChainedHashTable(const ChainedHashTable& other) : data(other.data) {}

    ChainedHashTable& operator=(const ChainedHashTable& other) {

        if (this != &other) 
        {
            data = other.data;
        }
        return *this;
    }

    size_t size() const noexcept override {

        size_t count = 0;
        for (const auto& list : data) 
        {
            count += list.getSize();
        }
        return count;
    }

    TList<Monom>& operator[](size_t pos) override {

        throw logic_error("Not implemented");
    }

    void deleteData(string key) override {

        size_t index = hashFunction(key);
        auto& list = data[index];
        auto it = list.begin();
        size_t position = 0;

        for (; it != list.end(); ++it, ++position) 
        {
            if (it->key == key) 
            {
                if (position == 0) { list.popFront(); }

            else { list.removeNodeAfter(position - 1); }
            
                return;
            }
        }
    }

    TList<Monom>* find(string key) override {

        size_t index = hashFunction(key);
        auto& list = data[index];
        auto it = list.begin();
        for (size_t i = 0; i < list.getSize(); ++i, ++it) 
        {
            if (it->key == key) 
            {
                return &(it->value);
            }
        }
        return nullptr;
    }

    void insert(string key, TList<Monom> value) override {

        size_t index = hashFunction(key);
        auto& list = data[index];
        if (!find(key))
        {
            list.pushBack({ key, value });
        }
    }

    void changeKey(string key, string newKey) override {

        size_t index = hashFunction(key);
        auto& list = data[index];
        auto it = list.begin();

        for (size_t i = 0; i < list.getSize(); ++i, ++it)
        {
            if (it->key == key) 
            {
                it->key = newKey;
                return;
            }
        }
    }

    ostream& print(ostream& stream, string name) const override {

        size_t index = hashFunction(name);
        const auto& list = data[index];
        for (auto it = list.cbegin(); it != list.cend(); ++it) 
        {
            if (it->key == name) 
            {
                stream << "Key: " << it->key << ", Value: " << it->value << endl;
                return stream;
            }
        }
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const ChainedHashTable& table) {

        table.print(stream, activeName);
    }


    void clear() {

        for (auto& list : data) { list.clear(); }
    }
};

#endif