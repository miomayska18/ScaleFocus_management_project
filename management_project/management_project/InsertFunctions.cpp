#include <iostream>
#include <string>
using namespace std;

string enterText(bool ignore)
{
	if (ignore) cin.ignore(/*0, '\n'*/);
	string text;
	getline(cin, text);

	return text;
}

double enterDouble()
{
	double num;
	cin >> num;
	return num;
}

int enterInt()
{
	int num;
	cin >> num;
	return num;
}

void printSpaces(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << " ";
	}
}

