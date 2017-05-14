#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool pairs(string data, int start, int end);

const int tableSize = 5000;

int pairTable[tableSize];//tells what the starting value of the pair this belongs to is

bool doneTable[tableSize];//tells whether I checked if this was part of pair

int table[tableSize];

int main()
{
	ifstream fin;
	ofstream fout;

	string data; //this is legit because I can access each individual element

	bool result;

	fin.open("pairs.in");
	fout.open("pairs.out");

	string a = "aabbccdd";
	string b = "aabaabcc";
	string c = "baabaacc";
	string d = "baaaabcc";	

	int count = 1;
	string resultStr = "no";
	
	//main loop for file processing
	while (fin >> data)
	{
		if (data.length() % 2 != 0)
			result = 0;
		else
		{
			for (int i = 0; i < tableSize; i++)
			{
				table[i] = -1;
			}
			result = pairs(data, 0, data.size());
			cout << "string computed as << " << result << endl;
		}
		if (result == false)
			resultStr = "no";
		else if (result == true)
			resultStr = "yes";
		else
			resultStr = "you fucked up";
		fout << count << " " << resultStr << endl;
		count++;
	}

	return 0;	
}

bool pairs(string data, int start, int end)
{
	int count = 1; // this so i can multiply to split
	string str1 = "";
	string str2 = "";

	//if (end < data.length() / 2) //yeah....
	//{
	//	cout << "errrp" << endl;
	//	return false;
	//}
	if (end - start == 0)
	{
		cout << "yup" << endl;
		return true;
	}
	

	//cout << data << endl;

	//so we have a for loop similar to the rod cutting problem
	for (int i = end - 2; i >= 0; i +=-2)
	{
		str1 = "";
		str2 = "";
		str1 = data.substr(i, count);
		cout << "str1: " << str1 << endl;
		str2 = data.substr(i + count, count);
		cout << "str2: " << str2 << endl;
		if (str1 == str2)
		{
			cout << "bool call" << endl;
			//if (pairs(data,start, i) == false)
			//{
			//	return true;
			//}
			if (pairs(data, start, i) == false)
			{ 
				cout << "return call" << endl;
				return pairs(data, start, i);
			}
			else if(pairs(data, start, i) == true)
			{
				i = 0;
			}
		}
		else if (str1.length() >= (data.length()/2))
		{
			cout << "str exceed half" << endl;
			return false;
		}
		count++;
			
		//if there was a pair, I need to throw away the pair
		//also after every pair found, jump over two to start again????
	}
	//cout << str1 << endl << str2 << endl;
}

