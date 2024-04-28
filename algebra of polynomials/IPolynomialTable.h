

// ��������� ��� ������� ���������, ������������ �������� �������� ���������� ����������.
class IPolynomialTable {
public:
    // ����� ����������� ����� ��� ���������� �������� � ������� �� ��������� �����.
    // ��������� ��� �������� � ��� ������� ��� ���������.
    virtual void addPolynomial(const std::string& name, const Polynomial& polynomial) = 0;

    // ����� ����������� ����� ��� ��������� �������� �� �����.
    // ���������� ������ �� �������, ��� ��������� �������� ������� �������� ����� �������.
    virtual Polynomial& getPolynomial(const std::string& name) = 0;

    // ����� ����������� ����� ��� �������� �������� �� ������� �� ��� �����.
    virtual void removePolynomial(const std::string& name) = 0;

    // ����� ����������� ����� ��� ������ ����������� ������� � ����� ������.
    // ��� ����� �������� ����� ���� ���������, ���������� � �������.
    virtual void print(std::ostream& os) const = 0;

    // ����������� ����������, �������������� ���������� ����������� �������� ����� ������� �����.
    virtual ~IPolynomialTable() {}

    // ����� ����������� ����� ��� ��������� ����� �������.
    // ��� ��� ����� �������������� ��� ������������� ������� � ���������������� ���������� ��� ������ ���������.
    virtual std::string getTableName() const = 0;

    // ������������� �������� ������, ������� ��������� ������������ ������� ����� ����������
    // ��������������� � �������� ������ (��������, std::cout).
    // �������� ���������� ���������� ������ print() ������, ��� ��������� ���������� �������� ���������� ������.
    friend std::ostream& operator<<(std::ostream& os, const IPolynomialTable& table) {
        table.print(os);  // ����� ������������ ������ print ��� ������ ����������� �������
        return os;
    }
};