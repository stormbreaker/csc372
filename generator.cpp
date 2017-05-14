#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>


using namespace std;

int main(int argc, char* argv[])
{
	ofstream fout;

	bool pairs;

	int character, length, num;

	fout.open("gen.in");

	srand(time(NULL));

	length = rand() % 1 + 5000;

	num = rand() % 1 + 20;

	for (int i = 0; i < num; i++)
	{

		pairs = rand() % 2;

		cout << pairs << endl;
		for (int j = 0; j < length; j++)
		{
			character = rand() % 25 + 122;
			fout << char(character);
		}
		fout << endl;
	}

		

	return 0;
}
