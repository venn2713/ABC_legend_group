#ifndef LINKEDTABLE_H
#define LINKEDTABLE_H



class LinkedTable : public AbstractTable {
private:
    struct TTableRec {
        string key;
        TList<Monom> value;
    };

    mutable TList<TTableRec> data{};

public:
    LinkedTable() = default;

    LinkedTable(const LinkedTable& other) : data(other.data) {}

    LinkedTable& operator=(const LinkedTable& other) {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }

    size_t size() const noexcept override { return data.getSize(); }

    TList<Monom>& operator[](size_t pos) override {

        return data.getValueAtPosition(pos).value;
    }

    void deleteData(string key) override {
        auto it = data.begin();
        size_t position = 0;
        for (; it != data.end(); ++it, ++position) {
            if (it->key == key)
            {
                if (position == 0) { data.popFront(); }
            
            else 
            {
                data.removeNodeAfter(position - 1);
            }
            return;
            }
        }
    }

    TList<Monom>* find(string key) override {

        auto it = data.begin();
        for (size_t i = 0; i < data.getSize(); ++i, ++it) {
            if (it->key == key) 
            {
            return &(it->value);
            }
        }
        return nullptr;
    }

    void insert(string key, TList<Monom> value) override {

        if (!find(key)) 
        {
            TTableRec newEntry;
            newEntry.key = key;
            newEntry.value = value;
            data.pushBack(newEntry);
        }
    }

    void changeKey(string key, string newKey) override {

        auto it = data.begin();
        for (; it != data.end(); ++it) 
        {
            if (it->key == key)
            {
                it->key = newKey;
                return;
            }
        }
    }

    ostream& print(ostream& stream, string name) const override {

        auto it = data.begin();
        for (size_t i = 0; i < data.getSize(); ++i, ++it) 
        {
            if (it->key == name)
            {
                stream << "Key: " << it->key << ", Value: " << it->value << endl;
                return stream;
            }
        }
        return stream;
    }

   friend ostream& operator<<(ostream& stream, const LinkedTable& table) {

       table.print(stream, activeName);
   }
};

#endif