#include "facilities.h"

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

double c_to_f(double t)
{
	return t * 9 / 5 + 32;
}

const int max_temp = 108;
const int min_temp = -44;
const char fahr = 'f';
const char cels = 'c';

void fill_from_file(vector<Reading>& readings, const string& name)
{
	ifstream ist(name.c_str());
	if (!ist) error("can't open input file ", name);
	Reading r;
	char ch;
	while (true) {
		ist >> r;
		if (!ist) break;   
		if (r.hour<0 || r.hour>23) error("hora fuera de rango");
		if (r.temperature<min_temp || r.temperature>max_temp)
			error("temperatura fuera de rango");
		ist >> ch;
		switch (ch) {
		case cels:
			r.temperature = c_to_f(r.temperature);
		case fahr:
			break;
		default:
			error("escala de temperatura ilegal ", ch);
		}
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
	cerr << "execpión: " << e.what() << endl;
}
catch (...) {
	cerr << "exepción\n";
}