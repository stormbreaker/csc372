/********************************************************************************
 * Program Name:  Program #1 Analysis of Algorithms
 * Author:  Benjamin Kaiser
 * Class:  CSC 372 - Analysis of Algorithms
 * Section:  M001
 * Instructor: Dr. A. Logar
 * Due Date:  October 4th, 2015
 * Dates Worked On:
 * 	September 29, 2015: Wrote main and file I/O
 * 	October 2, 2015:  Wrote primary recursive function
 * 	October 3, 2015:  Finalized primary recursive function with
 * 			  tabular recursion
 * 	October 4, 2015:  Documented and formatted
 * Description:  This program fulfills the requirements of Assignment 1 of
 * 		 CSC 372 - Analys of Algorithms Fall 2015.  The assignment
 * 		 requires a program which will process a file called pairs.in
 * 		 which contains any number of strings containing 1 to 5000
 * 		 characters.  The program determines whether a string is
 * 		 composed of repeated pairs.  An additional requirement is that
 * 		 it must process the given test cases in under a second.  
 * Usage:  There are no special usage instructions.  The program does not
 * 	   accept command line arguments and all neccessary file manipulations
 * 	   are hard-coded into the main function.
 * 	   Input file: pairs.in
 * 	   Output file: pairs.out
 * Compilation:  There are no special compilation instructions.  
 * 		 The program can simply be compiled using the g++ compiler as
 * 		 follows:
 * 		 g++ Prog1.cpp -o <executable>
 * Program Errors:  There are no known errors...
 *
********************************************************************************/ 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//The following constant is used to declare tables
const int tableSize = 5000;

//The following tables are used for tabular recursion
//	pairTable tells whether the substring from i to j is a pair
//	e.g. pairTable[i][j] == true shows that this is indeed a pair
//
//	doneTable tells whether this substring has been checked as a pair
//	e.g. doneTable[i][j] == true shows that this pair has been computed 
bool pairTable[tableSize][tableSize];
bool doneTable[tableSize][tableSize];

//Function prototypes
bool pairs(string data, int start, int end);
void reset(int needReset);

/*******************************************************************************
 * Function: main
 * Author: Benjamin Kaiser
 * Description:  This function is the main processing function of this program
 *		 This function opens up the files for input and output.  In
 *		 addition, the main loop handles reading in and counting how
 *		 many strings have been read in.  It also handles the setting
 *		 of the result and printing both the case (string) number and
 *		 the result to the output file.  At the end, the file streams
 *		 are closed to properly exit. 
 * Parameters: Not Applicable 
********************************************************************************/
int main()
  {
  //file streams for manipulation
  ifstream fin;
  ofstream fout;

  //string variable for manipulation
  string data; 

  //boolean variable for setting of result string
  bool result = 0;

  //file opening
  fin.open("pairs.in");
  fout.open("pairsExp.out");

  // variables for output
  // count is case number
  // resultStr is result of the string
  int count = 1;
  string resultStr = "no";
	
  //main loop for file processing
  while (fin >> data)
    {
    reset(data.length());
    if (data.length() % 2 != 0)
      result = 0;
    else
      {
      result = pairs(data, 0, data.size()); //recursive function call
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

/*******************************************************************************
 * Function: pairs
 * Author: Benjamin Kaiser
 * Description: This is the main recursive function for telling if a string
 * 		is composed of repeated pairs.  It accepts a string/substring
 * 		and start and end indices for this substring.  It then splits
 * 		another specified substring using math based on hypothetical
 * 		splits on indices.  The two substrings generated from the split
 * 		are then checked against each other to tell if they are
 * 		structurally equivalent. A base case tells if no more string
 * 		exists to be processed, then true is returned to the next level.
 *		A loop exists to check pairs composed of more than single
 *		characters (i.e. it checks pairs composed of 2, 4, 6, 8, etc.
 *		elements).  If at any point, the counter increments past
 *		more than half of the substring being processed, then
 *		it automatically returns false to the previous level
 *		since there can be no further pairs.  
 *		The dynamic attribute of this function uses the global
 *		tables pairTable and doneTable to store the boolean values
 *		to cut down on number of recursive calls made.
 *		It first checks to see if doneTable contains true.  If this
 *		is the case, then it returns whether the string described
 *		at those same indicies is a pair or not.  
 *		If at any point, the doneTable returns false, the pairTable
 *		analagous to the doneTable is computed and stored.  
 * Parameters: 
 * 	data: substring left to be processed
 * 	start: index where the substring begins
 * 	end: index where substring ends
*******************************************************************************/

bool pairs(string data, int start, int end)
  {
  //variable declarations used for processing
  int count = 1; // this so I can multiply to split the correct length
  string str1 = "";//string to hold split
  string str2 = "";//string to hold split
	
  //Base case
  if (end - start == 0)
    {
    return true;
    }
	

  //For loop processing through pairs in multiples of 2
  for (int i = end - 2; i >= 0; i +=-2)
    {
    //checks to see if processed this string
    if (doneTable[i][end] == true)
      {
      return pairTable[i][end];
      }
    //if not processed, then process
    else
      {
        str1 = "";
        str2 = "";
        str1 = data.substr(i, count);
        str2 = data.substr(i + count, count);
	//if the strings are equal, we need to check that this is the largest
	//	correct pair
        if (str1 == str2)
          {	
          bool test = pairs(data, start, i);
	  //if the subsequent string is paired, then we're good and can
	  //	safely return true		
          if (test == true)
            {
            pairTable[i][i + count + count] = true;
              return true;
            }
      }
    //if the substring exceeds half the the length of the main string,
    //	we return false to the previous level because we know there
    //	can be no more pairs
    else if (str1.length() >= (data.length()/2))
      {
      return false;
      }
    }
    //we computed this pair
    doneTable[i][i + count * 2] = true;
    count++;
    }
  }

/*******************************************************************************\
 * Function: reset
 * Author: Benjamin Kaiser
 * Description: This function resets the values in the global tables which are
 * 		used in the tabular recursion.  It sets both tables to contain 
 * 		completely false using a for loop.
 * Parameters: Not Applicable
*******************************************************************************/
void reset(int needReset)
  {
  for (int i = 0; i < needReset; i++)
    {
    for (int j= 0; j < needReset; j++)
      {
      pairTable[i][j] = false;
      doneTable[i][j] = false;
      }
    }
  }
