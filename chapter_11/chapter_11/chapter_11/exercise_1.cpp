#include "facilities.h"

int main()
try {
	cout << "Ingrese el nombre del archivo de entrada : ";
	string iname;
	cin >> iname;
	ifstream ifs(iname.c_str());
	if (!ifs) error("no se puede abrir el archivo de entrada ", iname);

	cout << "Ingrese el nombre del archivo de salida: ";
	string oname;
	cin >> oname;
	ofstream ofs(oname.c_str());
	if (!ofs) error("no se puede abrir el archivo de salida ", oname);

	char ch;
	while (ifs.get(ch)) {
		if (isalpha(ch)) ch = tolower(ch);
		ofs << ch;
	}
}
catch (exception& e) {
	cerr << "exepción: " << e.what() << endl;
}
catch (...) {
	cerr << "exepción\n";
}