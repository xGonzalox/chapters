#include "facilities.h"

// enumerator for number formats
enum num_format {
	decimal, octal, hexadecimal
};

ostream& operator<<(ostream& os, num_format nf)
{
	switch (nf) {
	case decimal:
		return os << "decimal\t";
	case octal:
		return os << "octal\t";
	case hexadecimal:
		return os << "hexadecimal";
	default:
		error("valor ilegal de número_formato");
	}
}

// print one line of the solution
void printnum(int n, num_format nf)
{
	cout << showbase;
	switch (nf) {
	case decimal:
		cout << dec << setw(6) << n;
		break;
	case octal:
		cout << oct << setw(6) << n;
		break;
	case hexadecimal:
		cout << hex << setw(6) << n;
		break;
	}
	cout << ' ' << nf << "\tconvierte a " << dec << setw(6) << n << ' ' << decimal << endl;
}

int main()
try {
	cout << "Ingrese enteros separados por espacios en notación decimal, octal o hexadecimal" << endl
		<< "(usando los prefijos 0 y 0x), cualquier letra para terminar:" << endl;
	int n = 0;
	char ch;
	while (cin >> ch) {
		if (ch == '0') {
			cin.get(ch);
			if (ch == 'x') {          // we have '0x' - hexadecimal
				cin >> hex >> n;
				printnum(n, hexadecimal);
			}
			else if (isdigit(ch)) { // we have '0' - octal
				cin.unget();
				cin >> oct >> n;
				printnum(n, octal);
			}
			else {                  // '0' without a number - octal 0
				cin.unget();
				printnum(0, octal);
			}
		}
		else if (isdigit(ch)) {     // decimal
			cin.unget();
			cin >> dec >> n;
			printnum(n, decimal);
		}
		else break; // not a number
	}
}
catch (exception& e) {
	cerr << "exepción: " << e.what() << endl;
}
catch (...) {
	cerr << "exepción\n";
}