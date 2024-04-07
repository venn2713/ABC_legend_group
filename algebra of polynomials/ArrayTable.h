#ifndef ABSTRACTTABLE_H
#define ABSTRACTTABLE_H


class ArrayTable : public AbstractTable {
private:
    struct TTableRec
    {
        string key;
        TList<Monom> value;
    };

    vector<TTableRec> data{};

public:
    ArrayTable() = default;

    ArrayTable(const ArrayTable& other) : data(other.data) {}

    ArrayTable& operator=(const ArrayTable& other) {

        if (this != &other) { data = other.data; }
        return *this;
    }

    size_t size() const noexcept override { return data.size(); }

    TList<Monom>& operator[](size_t pos) override { return data[pos].value; }

    void deleteData(string key) override {

        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].key == key)
            {
                data[i] = data[data.size() - 1];
                data.pop_back();

                return;
            }
        }
    }

    TList<Monom>* find(string key) override {

        for (auto& val : data)
        {
            if (val.key == key) { return &val.value; }
        }
        return nullptr;
    }

    void insert(string key, TList<Monom> value) override {

        if (find(key)) { return; }
        data.push_back({ key, value });
    }

    void changeKey(string key, string newKey) override {

        for (auto& entry : data)
        {
            if (entry.key == key) { entry.key = newKey; }
        }
    }

    ostream& print(ostream& stream, string name) const override {

        for (const auto& entry : data)
        {
            if (entry.key == name)
            {
                stream << "Key: " << entry.key << ", Value: " << entry.value << endl;
            }
        }
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const ArrayTable table) {

        table.print(stream, activeName);
    }
};
#endif