#include <iostream>
#include <string>
using namespace std;

string enterText()
{
	cin.ignore(0, '\n');
	string text;
	getline(cin, text);

	return text;
}

int enterInt()
{
	int num;
	cin >> num;
	return num;
}

/*double enterDouble()
{
	double num;
	cin >> num;
	return num;
}*/