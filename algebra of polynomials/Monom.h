#ifndef __MONOM_H__
#define __MONOM_H__


using namespace std;


class Monom {
public:
    double coef;
    int degree;

    Monom(double c, int d) : coef(c), degree(d) {}

    double calculationMonomial(double x, double y, double z) const {

        int exponents[3] = { degree / 100, (degree / 10) % 10, degree % 10 };
        double result = coef;

        for (int i = 0; i < 3; ++i)
        {
            result *= std::pow((i == 0 ? x : (i == 1 ? y : z)), exponents[i]);
        }

        return result;
    }

    int getDegree() const {
       return degree;
    }

    double getCoef() const {
       return coef;
    }

    bool operator==(const Monom& other) const {

        return degree == other.degree && abs(coef - other.coef) < 1e-10;
    }

    Monom operator+(const Monom& other) const {

        return Monom(coef + other.coef, degree);
    }

    Monom operator-(const Monom& other) const {

        return Monom(coef - other.coef, degree);
    }

    Monom operator*(const Monom& other) const {

        return Monom(coef * other.coef, degree + other.degree);
    }

    bool operator<(const Monom& other) const {

        return degree < other.degree;
    }

    bool operator!=(const Monom& other) const {
       return !(*this == other);
    }

    friend ostream& operator<<(ostream& stream, const Monom& monom) {

        int xdeg = monom.degree / 100;
        int ydeg = (monom.degree / 10) % 10;
        int zdeg = monom.degree % 10;

        stream << monom.coef;

        if (xdeg > 0)
        {
            stream << "x";
            if (xdeg > 1) { stream << "^" << xdeg; }
        }

        if (ydeg > 0)
        {
            if (xdeg > 0) { stream << ""; }
            stream << "y";

            if (ydeg > 1) { stream << "^" << ydeg; }
        }

        if (zdeg > 0)
        {
            if (xdeg > 0 || ydeg > 0) { stream << ""; }
            stream << "z";

            if (zdeg > 1) { stream << "^" << zdeg; }
        }
        return stream;
    }
};
#endif