#include "facilities.h"
#include <iostream>

struct Reading {
	int hour;           
	double temperature; 
	Reading() :hour(0), temperature(0) { }
	Reading(int h, double t) :hour(h), temperature(t) { }
};

bool operator<(const Reading& r1, const Reading& r2)
{
	return r1.temperature < r2.temperature;
}

ostream& operator<<(ostream& os, const Reading& r)
{
	return os << r.hour << ' ' << r.temperature;
}

istream& operator>>(istream& is, Reading& r)
{
	int hour;
	double temperature;
	is >> hour >> temperature;
	if (!is) return is;
	r = Reading(hour, temperature);
	return is;
}

const int max_temp = 108;
const int min_temp = -44;

void fill_from_file(vector<Reading>& readings, const string& name)
{
	ifstream ist(name.c_str());
	if (!ist) error("no se puede abrir el archivo de entrada ", name);
	Reading r;
	while (ist >> r) {
		if (r.hour<0 || r.hour>23) error("hora fuera de rango");
		if (r.temperature<min_temp || r.temperature>max_temp)
			error("temperatura fuera de rango");
		readings.push_back(r);
	}
}

int main()
try {
	vector<Reading> readings;
	fill_from_file(readings, "pics_and_txt/raw_temps.txt");

	sort(readings.begin(), readings.end());
	double median = readings[readings.size() / 2].temperature;

	double sum = 0;
	for (int i = 0; i<readings.size(); ++i) {
		sum += readings[i].temperature;
	}
	double avg = sum / readings.size();

	cout << "temperatura media: " << median << " F" << endl;
	cout << "temperatura promedio: " << avg << " F" << endl;
}
catch (exception& e) {
	cerr << "excepción: " << e.what() << endl;
}
catch (...) {
	cerr << "excepción\n";
}