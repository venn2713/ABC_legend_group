#include "Polinom.h"
#include "string"


int main() {

	setlocale(LC_ALL, "Russian");
	system("title Полиномиальный калькулятор");

	Polinom pol1("pol1", "2x+4y");
	cout << pol1 << endl;

	Polinom pol2("pol2", "6x-3z^3");
	cout << pol2 << endl;

	Polinom pol3 = pol1.MultiplyByConst(3);
	pol3.setName("pol3");
	cout << pol3;

	return 0;
}
