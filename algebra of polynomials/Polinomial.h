

// Определение класса для термов полинома.
class PolynomialTerm {
public:
    double coefficient;  // Коэффициент терма полинома.
    int x_exp, y_exp, z_exp;  // Степени переменных x, y, z.

    // Конструктор класса с инициализацией коэффициента и степеней переменных.
    PolynomialTerm(double coef, int x, int y, int z)
        : coefficient(coef), x_exp(x), y_exp(y), z_exp(z) {}

    // Оператор сравнения "меньше", используется для сравнения термов по степеням.
    bool operator<(const PolynomialTerm& other) const {
        if (x_exp != other.x_exp) return x_exp < other.x_exp;  // Сначала сравниваем по x.
        if (y_exp != other.y_exp) return y_exp < other.y_exp;  // Затем по y.
        return z_exp < other.z_exp;                            // Наконец, по z.
    }


    // Оператор сравнения "больше", основанный на операторе "меньше".
    bool operator>(const PolynomialTerm& other) const {
        return other < *this;  // Используем оператор "меньше" для сравнения в обратном порядке.
    }

    // Оператор сравнения "меньше или равно", основанный на операторе "больше".
    bool operator<=(const PolynomialTerm& other) const {
        return !(*this > other);  // Если терм не больше другого, то он либо меньше, либо равен.
    }

    // Оператор сравнения "больше или равно", также основанный на операторе "меньше".
    bool operator>=(const PolynomialTerm& other) const {
        return !(*this < other);  // Если терм не меньше другого, то он либо больше, либо равен.
    }

    // Оператор сравнения на равенство, проверяет равенство всех полей терма.
    bool operator==(const PolynomialTerm& other) const {
        return x_exp == other.x_exp && y_exp == other.y_exp && z_exp == other.z_exp && coefficient == other.coefficient;
    }

    // Оператор сравнения на неравенство, основанный на операторе равенства.
    bool operator!=(const PolynomialTerm& other) const {
        return !(*this == other);  // Просто инвертируем результат оператора равенства.
    }
};
// Класс представляющий полином, содержащий список термов.
class Polynomial {
    std::list<PolynomialTerm> terms; // список членов полинома, используя STL контейнер std::list

public:
    const std::list<PolynomialTerm> getTerms() const {
        return terms;
    }

    bool isNumber() const {
        return terms.size() == 1 && terms.front().x_exp == 0 && terms.front().y_exp == 0 && terms.front().z_exp == 0;
    }
    // Конструктор по умолчанию
    Polynomial() = default; // Использует стандартный конструктор для инициализации списка

    // Конструктор с параметром строка, который парсит строку с выражением полинома
    Polynomial(const std::string& expression) {
        parseExpression(expression); // Парсинг переданной строки при создании объекта
    }

    // Конструктор копирования
    Polynomial(const Polynomial& other) : terms(other.terms) {} // Копирует список термов из другого полинома

    // Конструктор перемещения
    Polynomial(Polynomial&& other) noexcept : terms(std::move(other.terms)) {} // Перемещает список термов, используя move-семантику

    // Деструктор
    ~Polynomial() = default; // Использует стандартный деструктор

    std::string toString() const {
        std::ostringstream oss;
        bool isFirst = true;
        for (auto it = terms.rbegin(); it != terms.rend(); ++it) {
            const auto& term = *it;
            if (term.coefficient == 0) continue; // Пропуск членов с нулевым коэффициентом

            if (!isFirst) {
                oss << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) oss << "-";
                isFirst = false;
            }

            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                oss << fabs(term.coefficient);
            }
            if (term.x_exp > 0) {
                oss << "x";
                if (term.x_exp != 1) oss << "^" << term.x_exp;
                else oss << "^1"; // Добавляем явное указание степени 1
            }
            if (term.y_exp > 0) {
                oss << "y";
                if (term.y_exp != 1) oss << "^" << term.y_exp;
                else oss << "^1"; // Добавляем явное указание степени 1
            }
            if (term.z_exp > 0) {
                oss << "z";
                if (term.z_exp != 1) oss << "^" << term.z_exp;
                else oss << "^1"; // Добавляем явное указание степени 1
            }
        }
        if (isFirst) oss << "0";
        return oss.str();
    }

    // Парсер вводимого полинома
    void parseExpression(const std::string& input_poly) {
        // Удаление всех пробелов из входной строки и замена "-" на "+-", чтобы упростить разбиение на термы
        std::string processed_poly = std::regex_replace(input_poly, std::regex("\\s+"), "");
        processed_poly = std::regex_replace(processed_poly, std::regex(","), ".");
        processed_poly = std::regex_replace(processed_poly, std::regex("-"), "+-");

        // Регулярное выражение для разбиения полинома на термы
        std::regex pattern(R"(([-+]?\d*\.?\d*)(x\^(\d*))?(y\^(\d*))?(z\^(\d*))?)");
        std::regex plus_regex("\\+");
        std::sregex_token_iterator iter(std::begin(processed_poly), std::end(processed_poly), plus_regex, -1);
        std::sregex_token_iterator end;

        for (; iter != end; ++iter) {
            std::string monom = *iter;
            if (monom.empty()) continue;
            std::smatch match;
            if (std::regex_match(monom, match, pattern)) {
                // Получение коэффициента и степеней, и добавление терма в список
                double coef = match.str(1).empty() || match.str(1) == "+" ? 1.0 : match.str(1) == "-" ? -1.0 : std::stod(match.str(1));
                int x_deg = match.length(3) > 0 ? std::stoi(match.str(3)) : 0;
                int y_deg = match.length(5) > 0 ? std::stoi(match.str(5)) : 0;
                int z_deg = match.length(7) > 0 ? std::stoi(match.str(7)) : 0;

                addTerm(coef, x_deg, y_deg, z_deg);
            }
        }
    }


    // Добавление терма в полином
    void addTerm(double coefficient, int x_exp, int y_exp, int z_exp) {
        if (coefficient == 0) {
            return; // Если коэффициент равен нулю, терм не добавляется
        }

        PolynomialTerm newTerm(coefficient, x_exp, y_exp, z_exp);
        // Поиск места для вставки терма в упорядоченном списке
        auto it = std::find_if(terms.begin(), terms.end(), [&](const PolynomialTerm& term) {
            return (term.x_exp > x_exp) ||
                (term.x_exp == x_exp && term.y_exp > y_exp) ||
                (term.x_exp == x_exp && term.y_exp == y_exp && term.z_exp >= z_exp);
            });

        if (it != terms.end() && it->x_exp == x_exp && it->y_exp == y_exp && it->z_exp == z_exp) {
            // Если терм с такими же степенями уже существует, обновляется его коэффициент
            it->coefficient += coefficient;
            if (it->coefficient == 0) {
                // Если коэффициент становится нулевым, терм удаляется
                terms.erase(it);
            }
        }
        else {
            // Вставка нового терма на нужное место
            terms.insert(it, newTerm);
        }
    }

    double evaluate(double x, double y, double z) const {
        double result = 0.0;
        for (const auto& term : terms) {
            result += term.coefficient * pow(x, term.x_exp) * pow(y, term.y_exp) * pow(z, term.z_exp);
        }
        return result;
    }

    // Оператор сложения двух полиномов
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this; // Копируем текущий полином в результат
        for (const auto& term : other.terms) {
            result.addTerm(term.coefficient, term.x_exp, term.y_exp, term.z_exp);
        }
        return result;
    }

    // Оператор сравнения двух полиномов на равенство
    bool operator==(const Polynomial& other) const {
        return terms == other.terms; // Сравниваем списки термов
    }

    // Оператор вычитания двух полиномов
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result = *this; // Копируем текущий полином в результат
        for (const auto& term : other.terms)
            result.addTerm(-term.coefficient, term.x_exp, term.y_exp, term.z_exp); // Добавляем с противоположным знаком
        return result;
    }

    // Оператор вычитания числа их полинома
    Polynomial operator-(double scalar) const {
        Polynomial result = *this;
        result.addTerm(-scalar, 0, 0, 0); // Уменьшаем константный член
        return result;
    }

    // Оператор сложения числа с полиномом
    Polynomial operator+(double scalar) const {
        Polynomial result = *this;
        result.addTerm(scalar, 0, 0, 0); // Добавляем константный член
        return result;
    }

    // Оператор умножения полиномов
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        for (const auto& term1 : terms) {
            for (const auto& term2 : other.terms) {
                double new_coef = term1.coefficient * term2.coefficient;
                int new_x_exp = term1.x_exp + term2.x_exp;
                int new_y_exp = term1.y_exp + term2.y_exp;
                int new_z_exp = term1.z_exp + term2.z_exp;
                result.addTerm(new_coef, new_x_exp, new_y_exp, new_z_exp);
            }
        }
        return result;
    }



    // Оператор умножения полинома на число (полином * число)
    Polynomial operator*(double scalar) const {
        Polynomial result;
        for (const auto& term : terms) {
            double new_coef = term.coefficient * scalar;
            if (new_coef != 0) {  // избежать добавления нулевого терма
                result.addTerm(new_coef, term.x_exp, term.y_exp, term.z_exp);
            }
        }
        return result;
    }

    // Оператор умножения числа на полином (число * полином)
    friend Polynomial operator*(double scalar, const Polynomial& poly) {
        return poly * scalar;
    }

    // Оператора присваивания копированием
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {  // Проверка на самоприсваивание
            terms.clear();  // Очистить текущий список термов
            terms = other.terms;  // Копировать термы из другого полинома
        }
        return *this;
    }

    // Вывод полином
    void print() const {
        bool isFirst = true;
        for (const auto& term : terms) {
            if (term.coefficient == 0) continue;  // Skip zero coefficients

            if (!isFirst) {
                std::cout << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) std::cout << "-";
                isFirst = false;
            }

            // Print absolute value of the coefficient if it's not 1 or -1, except when all exponents are 0
            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                std::cout << fabs(term.coefficient);
            }
            if (term.x_exp > 0) std::cout << "x" << (term.x_exp > 1 ? "^" + std::to_string(term.x_exp) : "");
            if (term.y_exp > 0) std::cout << "y" << (term.y_exp > 1 ? "^" + std::to_string(term.y_exp) : "");
            if (term.z_exp > 0) std::cout << "z" << (term.z_exp > 1 ? "^" + std::to_string(term.z_exp) : "");
        }
        if (isFirst) std::cout << "0";  // If all terms were zero, print "0"
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        p.print(os);
        return os;
    }

    void print(std::ostream& os) const {
        bool isFirst = true;
        for (const auto& term : terms) {
            if (term.coefficient == 0) continue; // Пропуск членов с нулевым коэффициентом

            if (!isFirst) {
                os << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) os << "-";
                isFirst = false;
            }

            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                os << fabs(term.coefficient);
            }
            if (term.x_exp > 0) os << "x" << (term.x_exp > 1 ? "^" + std::to_string(term.x_exp) : "");
            if (term.y_exp > 0) os << "y" << (term.y_exp > 1 ? "^" + std::to_string(term.y_exp) : "");
            if (term.z_exp > 0) os << "z" << (term.z_exp > 1 ? "^" + std::to_string(term.z_exp) : "");
        }
        if (isFirst) os << "0";
        os << std::endl;
    }
};
