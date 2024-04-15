#include "Polinom.h"
#include "string"


int main() {

	setlocale(LC_ALL, "Russian");
	system("title Полиномиальный калькулятор");

	Polinom pol1("pol1", "4x^2y^2+3x^3y^2");

	pol1.setActiveIndex(4);

	cout << pol1 << endl;

	pol1.setName("pol1", "newName");

	cout << pol1 << endl;
	
	Polinom pol2("pol2", "3x^2y^2+2x^3z^2");
	cout << pol2 << endl;

	Polinom pol3 = pol1 + pol2;
	cout << pol3 << endl;

	Polinom pol4 = pol1 - pol2;
	cout << pol4 << endl;

	double res = pol4.Calculation(1, 1, 1);

	cout << res << endl;

	cout << pol1.MultiplyByConst(100) << endl;

	return 0;
}
