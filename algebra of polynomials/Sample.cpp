#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "StackAndPostfix.h"
#include "design.h"
#define SIZE 7

using namespace std;

enum KEYS {
    UP = 72, DOWN = 80, ENTER = 13, LEFT = 75
};

enum  Menu {
    add_polynomial = 0, del_polynomial = 1, algebraic_expression = 2, in_point = 3, set_active = 4, print_active = 5, EXIT = 6
};

char Menu[7][50] = {
   "Äîáàâëåíèå ïîëèíîìà",
   "Óäàëåíèå ïîëèíîìà",
   "Àëãåáðàè÷åñêîå âûðàæåíèå",
   "Âû÷èñëåíèå â òî÷êå",
   "Ñìåíà àêòèâíîé òàáëèöû",
   "Âûâîä àêòèâíîé òàáëèöû",
   "Âûõîä"
};
int active_menu = 0;

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("title Ïîëèíîìèàëüíûé êàëüêóëÿòîð");
    SMALL_RECT window;
    COORD buf;
    getwindow(&window, &buf);

    vector<string> tables_name = {
    "PolynomialListTable",
    "PolynomialArrayTable",
    "PolynomialOrderedTable",
    "PolynomialRBTreeTable",
    "PolynomialHashTable",
    "ChainedPolynomialHashTable"
    };

    int variable_x;
    char ch;
    double x, y, z = 1.0, res;
    string name = "", pol, infix_string;
    TableManager manager;
    PostfixCalculator calc(manager);

    clrscr();
    variable_x = (window.Left + window.Right) / 30;
    textcolor(MAGENTA);
    gotoxy(variable_x + 25, wherey() + 5);
    cout << "Äîáðî ïîæàëîâàòü â ïðîãðàììó, êîòîðàÿ ðàáîòàåò c \"Ïîëèíîìàìè\"" << endl;
    gotoxy(variable_x + 5, wherey() + 3);

    cout << "Íåîáõîäèìî ââåñòè ïîëèíîì äëÿ äîáàâëåíèÿ â òàáëèöû (Ìîíîìû ðàçäåëÿþòñÿ çíàêàìè + èëè -, ïðèìåð: 2x^3y^3+3x^2): " << endl;
    getline(cin, pol);
    cout << "Ââåäèòå èìÿ äëÿ ïîëèíîìà (ïðèìåð: pol1): ";
    getline(cin, name);
    manager.addPolynomialToAllTables(name, Polynomial(pol));
    
    gotoxy(variable_x + 35, wherey() + 2);


    textcolor(MAGENTA);
    system("cls");

    while (1) {
        hidecursor();
        system("cls");
        for (int i = 0; i < SIZE; i++) {
            if (i == active_menu)
                textcolor(GREEN);
            else
                textcolor(YELLOW);
            cout << Menu[i] << endl;
        }
        ch = _getch();
        if (ch == -32)
            ch = _getch();

        switch (ch)
        {
        case UP:
            if (active_menu > 0)
                active_menu--;
            break;
        case DOWN:
            if (active_menu < SIZE - 1)
                active_menu++;
            break;
        case ENTER:
            switch (active_menu)
            {
            case add_polynomial:
                system("cls");
                cout << "Ââåäèòå ïîëèíîì äëÿ äîáàâëåíèÿ â òàáëèöû (Ìîíîìû ðàçäåëÿþòñÿ çíàêàìè + èëè -, ïðèìåð: 2x^3y^3+3x^2): ";
                getline(cin, pol);
                cout << "Ââåäèòå èìÿ äëÿ ïîëèíîìà (ïðèìåð: pol1): ";
                getline(cin, name);

                manager.addPolynomialToAllTables(name, Polynomial(pol));
                system("pause");
                break;

            case del_polynomial:
                system("cls");

                cout << "Ââåäèòå èìÿ ïîëèíîìà äëÿ óäàëåíèÿ èç âñåõ òàáëèö (ïðèìåð: pol1): ";
                getline(cin, name);

                manager.removePolynomialFromAllTables(name);

                system("pause");
                break;

            case algebraic_expression:
                system("cls");
                cout << "Ââåäèòå àëãåáðàè÷åñêîå âûðàæåíèå (ïðèìåð: 2 * pol1 + 2 * pol2 + 3.6 * q - const6): ";
                getline(cin, infix_string);
                try {
                    
                    cout << "Infix: \"" << infix_string << "\"" << endl;
                    string postfix_string = calc.infixToPostfix(infix_string);
                    cout << "Postfix: \"" << postfix_string << "\"" << endl;
                    Polynomial result = calc.evaluate(postfix_string);
                    cout << "Ðåçóëüòàò: " << result << endl;
                    cout << "Ââåäèòå èìÿ äëÿ ïîëó÷åííîãî ïîëèíîìà: ";
                    getline(cin, name);
                    manager.addPolynomialToAllTables(name, result);
                    
                }
                catch (const exception& e) {
                    cout << "An error occurred: " << e.what() << endl;
                }
                system("pause");
                break;

            case in_point:
                system("cls");
                cout << "Ââåäèòå èìÿ ïîëèíîìà äëÿ âû÷èñëåíèÿ â òî÷êå (ïðèìåð: pol1): ";
                getline(cin, name);
                cout << "Ââåäèòå çíà÷åíèå x: ";
                cin >> x;
                cout << "Ââåäèòå çíà÷åíèå y: ";
                cin >> y;
                cout << "Ââåäèòå çíà÷åíèå z: ";
                cin >> z;
                res = manager.getActiveTable()->getPolynomial(name).evaluate(x, y, z);
                
                manager.getActiveTable()->getPolynomial(name).print();
                cout << "Îòâåò: " << res << endl;

                system("pause");
                break;

            case set_active:
                system("cls");

                for (int i = 0; i < 6; i++)
                    cout << i + 1 << ". " << tables_name[i] << endl;

                int t;

                cout << "Ââåäèòå èíäåêñ: ";
                cin >> t;
                manager.setActiveTableByName(tables_name[t - 1]);
                cin.ignore(1, '\n');
                system("pause");
                break;

            case print_active:
                system("cls");
                
                manager.printActiveTable();
                system("pause");
                break;

            case EXIT:
                exit(0);
                break;
            }
        }
    }
    return 0;
}
