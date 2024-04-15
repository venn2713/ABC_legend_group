#include "Polinom.h"


tablesControl Polinom::tables(0);
int Polinom::dublicate = 0;

Polinom::Polinom(const Polinom& other) {

    for (size_t i = 0; i < other.tables.getDataFromActive(other.name).getSize(); ++i)
    {
        AddMonom(other.tables.getDataFromActive(other.name).getValueAtPosition(i));
    }

    this->name = other.name;
    tables.insertIntoAll(this->name, monoms);
}

Polinom::Polinom(const string& name, const string& polinomStr) : name(name) {

    regex monomPattern(R"(\s*([-+]?\d*\.?\d*)\s*(x(\^\d+)?)?\s*(y(\^\d+)?)?\s*(z(\^\d+)?)?\s*)");

    sregex_iterator monomIteratorBegin(polinomStr.begin(), polinomStr.end(), monomPattern);
    sregex_iterator monomIteratorEnd;

    for (auto it = monomIteratorBegin; it != monomIteratorEnd; ++it)
    {
        const smatch& match = *it;

        if (match[1].str().empty() && !match[2].matched &&
            !match[4].matched && !match[6].matched) {
            continue;
        }

        double monomCoefficient = 1.0;
        int monomXDegree = 0;
        int monomYDegree = 0;
        int monomZDegree = 0;

        if (!match[1].str().empty()) { monomCoefficient = stod(match[1].str()); }

        if (!match[3].str().empty()) { monomXDegree = stoi(match[3].str().substr(1)); }

        else if (match[2].matched) { monomXDegree = 1; }

        if (!match[5].str().empty()) { monomYDegree = stoi(match[5].str().substr(1)); }

        else if (match[4].matched) { monomYDegree = 1; }

        if (!match[7].str().empty()) { monomZDegree = stoi(match[7].str().substr(1)); }

        else if (match[6].matched) { monomZDegree = 1; }

        unsigned int monomTotalDegree = monomXDegree * 100 + monomYDegree * 10 + monomZDegree;

        AddMonom(Monom(monomCoefficient, monomTotalDegree));
    }

    combineLikeTerms();
    tables.insertIntoAll(this->name, monoms);
}

void Polinom::AddMonom(const Monom& monom) {

    if (monom.coef != 0) { monoms.pushBack(monom); }
}

string Polinom::getName() { return name; }

void Polinom::setName(string oldName, string newName) {

    this->name = newName;
    tables.changeKeyFromAll(oldName, name);
}

size_t Polinom::getSize() const {
   return monoms.getSize();
}

void Polinom::combineLikeTerms() {

    vector<Monom> monomVector;
    while (!monoms.isEmpty())
    {
        monomVector.push_back(monoms.getFront());
        monoms.popFront();
    }

    sort(monomVector.begin(), monomVector.end(), [](const Monom& a, const Monom& b) { return a.degree > b.degree; });

    for (size_t i = 0; i < monomVector.size(); i++)
    {
        if (i < monomVector.size() - 1 &&
            monomVector[i].degree == monomVector[i + 1].degree)
        {
            monomVector[i + 1].coef += monomVector[i].coef;
            monomVector[i].coef = 0;
        }
    }

    monomVector.erase(remove_if(monomVector.begin(), monomVector.end(), [](const Monom& m) { return m.coef == 0; }), monomVector.end());

    for (const auto& monom : monomVector) { monoms.pushBack(monom); }
}

void Polinom::deletePolinom() {

    tables.deleteFromAll(name);
}

bool Polinom::isEmpty() {

    return monoms.isEmpty();
}

void Polinom::setActiveIndex(int idx) { tables.setActiveIndex(idx); }

double Polinom::Calculation(double x, double y, double z) const {

    double sum = 0.0;
    for (size_t i = 0; i < monoms.getSize(); ++i)
    {
        sum += tables.getDataFromActive(name).getValueAtPosition(i).calculationMonomial(x, y, z);
    }
    return sum;
}

Polinom Polinom::MultiplyByConst(int constant) const {

    Polinom res;

    for (size_t i = 0; i < monoms.getSize(); ++i)
    {
        Monom cur = monoms.getValueAtPosition(i);
        double newCoef = cur.coef * constant;
        res.AddMonom(Monom(newCoef, cur.degree));
    }

    res.name = to_string(dublicate++);
    tables.insertIntoAll(res.name, res.monoms);
    return res;
}

Polinom& Polinom::operator=(const Polinom& other) {

    if (this == &other) { return *this; }

    monoms.clear();

    for (size_t i = 0; i < other.tables.getDataFromActive(other.name).getSize(); ++i)
    {
        AddMonom(other.tables.getDataFromActive(other.name).getValueAtPosition(i));
    }

    this->name = other.name;

    tables.insertIntoAll(this->name, monoms);
    return *this;
}

Polinom Polinom::operator-(const Polinom& other) const {

    Polinom res = *this;

    for (size_t i = 0; i < other.monoms.getSize(); ++i)
    {
        res.AddMonom(Monom(-other.monoms.getValueAtPosition(i).coef, other.monoms.getValueAtPosition(i).degree));
    }

    res.combineLikeTerms();

    res.name = to_string(dublicate++);
    tables.insertIntoAll(res.name, res.monoms);
    return res;
}

Polinom Polinom::operator+(const Polinom& other) const {

    Polinom res = *this;

    for (size_t i = 0; i < other.monoms.getSize(); ++i)
    {
        res.AddMonom(other.monoms.getValueAtPosition(i));
    }

    res.combineLikeTerms();

    res.name = to_string(dublicate++);
    tables.insertIntoAll(res.name, res.monoms);
    return res;
}

Polinom Polinom::operator*(const Polinom& other) const {

    Polinom res;

    for (size_t i = 0; i < this->monoms.getSize(); ++i)
    {
        for (size_t j = 0; j < other.monoms.getSize(); ++j)
        {
            double productCoefficient = this->monoms.getValueAtPosition(i).coef * other.monoms.getValueAtPosition(j).coef;
            unsigned int sumDegree = this->monoms.getValueAtPosition(i).degree + other.monoms.getValueAtPosition(j).degree;
            res.AddMonom(Monom(productCoefficient, sumDegree));
        }
    }

    res.combineLikeTerms();

    res.name = to_string(dublicate++);
    tables.insertIntoAll(res.name, res.monoms);
    return res;
}
