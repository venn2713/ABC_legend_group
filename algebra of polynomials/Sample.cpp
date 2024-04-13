#include "Polinom.h"
#include "string"


int main() {

	setlocale(LC_ALL, "Russian");
	system("title Полиномиальный калькулятор");

	Polinom pol1("pol1", "4x^2y^2+3x^3y^2");
	cout << pol1 << endl;
	
	Polinom pol2("pol2", "3x^2y^2+2x^3z^2");
	cout << pol2 << endl;

	Polinom pol3 = pol1 + pol2;
	cout << pol3;

	Polinom pol4 = pol1 - pol2;
	cout << pol4;

	return 0;
}
