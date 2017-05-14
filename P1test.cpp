#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool pairs(string data, int start, int end);
void reset();


const int tableSize = 5000;

bool pairTable[tableSize][tableSize];//tells what the starting value of the pair this belongs to is

bool doneTable[tableSize][tableSize];//tells whether I checked if this was part of pair


int main()
{
	ifstream fin;
	ofstream fout;

	string data; //this is legit because I can access each individual element

	bool result = 0;

	fin.open("pairs6.in");
	fout.open("pairs6.out");

	string a = "aabbccdd";
	string b = "aabaabcc";
	string c = "baabaacc";
	string d = "baaaabcc";	

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
			//cout << "string computed as " << result << endl;
		}
		if (result == false)
			resultStr = "no";
		else if (result == true)
			resultStr = "yes";
		else
			resultStr = "something bad happened";
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
	
	//need to check to see if this has been done
	//	if has been done need to return the table of strings	

	
	if (end - start == 0)
	{
		//cout << "yup" << endl;
		return true;
	}
	

	//cout << data << endl;

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
			//cout << "str1: " << str1 << endl;
			str2 = data.substr(i + count, count);
			//cout << "str2: " << str2 << endl;
			if (str1 == str2)
			{
				//table needs to be called here
				//the start and end of the 2d array are the start and
				//end of the pair not of the substring to be computed
				
				bool test = pairs(data, start, i);
					
				//cout << "bool call" << endl;
				if (test/*pairs(data,start,i)*/ == true)
				{
					pairTable[i][i + count + count] = true;
					//cout << "we might have a winner!" << endl;
					return true; //pairs(data, start, i);
				}
				//if (pairs(data, start, i) == false)
				//{ 
					//return pairs(data, start, i);
				//}
			}
			else if (str1.length() >= (data.length()/2))
			{
				//cout << "str exceed half" << endl;
				return false;
			}
		}
		doneTable[i][i + count * 2] = true;
		count++;
			
		//if there was a pair, I need to throw away the pair
		//also after every pair found, jump over two to start again????
	}
	//cout << str1 << endl << str2 << endl;
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
