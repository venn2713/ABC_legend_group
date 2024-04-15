#ifndef ORDEREDARRAYTABLE_H
#define ORDEREDARRAYTABLE_H



class OrderedArrayTable : public AbstractTable {
private:
    struct TTableRec 
    {
        string key;
        TList<Monom> value;
    };

    vector<TTableRec> data;

public:
    OrderedArrayTable() = default;

    OrderedArrayTable(const OrderedArrayTable& other) : data(other.data) {}

    OrderedArrayTable& operator=(const OrderedArrayTable& other) {

        if (this != &other) 
        {
            data = other.data;
        }
        return *this;
    }

    size_t size() const noexcept override {

        return data.size();
    }

    TList<Monom>& operator[](size_t pos) override {

        return data[pos].value;
    }

    void deleteData(string key) override {

        auto it = find_if(data.begin(), data.end(), [&](const TTableRec& rec) 
        {
            return rec.key == key;
        });
        if (it != data.end()) 
        {
            data.erase(it);
        }
    }

    TList<Monom>* find(string key) override {

        auto it = find_if(data.begin(), data.end(), [&](const TTableRec& rec) 
        {
            return rec.key == key;
        });
        if (it != data.end()) 
        {
            return &(it->value);
        }
        return nullptr;
    }

    void insert(string key, TList<Monom> value) override {

        TTableRec rec{ key, value };
        auto it = lower_bound(data.begin(), data.end(), rec, [&](const TTableRec& a, const TTableRec& b)
        {
            return a.key < b.key;
        });
        data.insert(it, rec);
    }

    void changeKey(string key, string newKey) override {

        auto it = find_if(data.begin(), data.end(), [&](const TTableRec& rec) 
        {
            return rec.key == key;
        });
        if (it != data.end())
        {
            it->key = newKey;
            sort(data.begin(), data.end(), [&](const TTableRec& a, const TTableRec& b) 
            {
                return a.key < b.key;
            });
        }
    }

    ostream& print(ostream& stream, string name) const override {

        auto it = find_if(data.begin(), data.end(), [&](const TTableRec& rec)
        {
            return rec.key == name;
        });
        if (it != data.end()) 
        {
            stream << "Key: " << it->key << ", Value: " << it->value << endl;
        }
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const OrderedArrayTable& table) {

        table.print(stream, activeName);
    }
};

#endif