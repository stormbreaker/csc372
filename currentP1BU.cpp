#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool pairs(string data, int start, int end);
void reset();


const int tableSize = 5000;

bool pairTable[tableSize][tableSize];//global table tells if there is a pair

bool doneTable[tableSize][tableSize];//global table tells if have computed already

int main()
{
	ifstream fin;
	ofstream fout;

	string data; //this is legit because I can access each individual element

	bool result = 0;

	fin.open("pairs.in");
	fout.open("pairs.out");

	int count = 1;
	string resultStr = "no";
	
	//main loop for file processing
	while (fin >> data)
	{
		reset();
		if (data.length() % 2 != 0)
			result = 0;
		else
		{
			result = pairs(data, 0, data.size());
		}
		if (result == false)
			resultStr = "no";
		else if (result == true)
			resultStr = "yes";
		fout << count << " " << resultStr << endl;
		count++;
	}

	return 0;	
}

bool pairs(string data, int start, int end)
{
	int count = 1; // this so i can multiply to split
	string str1 = "";//string to hold split
	string str2 = "";//string to hold split
	
	//comment this
	if (end - start == 0)
	{
		return true;
	}
	

	//so we have a for loop similar to the rod cutting problem
	for (int i = end - 2; i >= 0; i +=-2)
	{
		if (doneTable[i][end] == true)
		{
			return pairTable[i][end];
		}
		else
		{
			str1 = "";
			str2 = "";
			str1 = data.substr(i, count);
			str2 = data.substr(i + count, count);
			if (str1 == str2)
			{	
				bool test = pairs(data, start, i);
					
				if (test == true)
				{
					pairTable[i][i + count + count] = true;
					return true;
				}
			}
			else if (str1.length() >= (data.length()/2))
			{
				return false;
			}
		}
		doneTable[i][i + count * 2] = true;
		count++;
	}
}
void reset()
{
	for (int i = 0; i < tableSize; i++)
	{
		for (int j= 0; j < tableSize; j++)
		{
			pairTable[i][j] = false;
			doneTable[i][j] = false;
		}
	}
}
