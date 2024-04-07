#include "TList.h"


static string activeName;


class AbstractTable {
public:
    virtual ~AbstractTable() {}

    virtual size_t size() const noexcept = 0;

    virtual void deleteData(string key) = 0;

    virtual TList<Monom>* find(string key) = 0;

    virtual void changeKey(string key, string newKey) = 0;

    virtual void insert(string key, TList<Monom> value) = 0;

    virtual TList<Monom>& operator[](size_t pos) = 0;

    virtual ostream& print(ostream& stream, string name) const = 0;

    friend ostream& operator<<(ostream& stream, const AbstractTable& table) {

        table.print(stream, activeName);
        return stream;
    }
};