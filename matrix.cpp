#include <iostream>
#include <iomanip>
#include <limits.h>
using namespace std;

const int MAX = 200;
int m_table[MAX][MAX];
int s_table[MAX][MAX];

///////////////////////////////////////////////////////////////

void print_tables(int n)
{
	int i;
	int j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			if (j < i)
				cout << "        ";
			else
				cout << setw(8)<< m_table[i][j];
				cout << endl;
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			if (j < i)
				cout << "    ";
			else
				cout << setw(4) << s_table[i][j];
				cout << endl;
	}
}
///////////////////////////////////////////////////////////////

                                                                                                    void init_tables(int n)
                                                                                                      {
                                                                                                        int i;
                                                                                                          int j;

                                                                                                            // diagonal is zero
                                                                                                              for (i = 1; i <= n; i++)
                                                                                                                  {
                                                                                                                      m_table[i][i] = 0;
                                                                                                                          s_table[i][i] = 0;
                                                                                                                              }

                                                                                                                                // start off diagonal at -1
                                                                                                                                  for (i = 1; i <= n; i++)
                                                                                                                                      for (j = i + 1; j <= n; j++)
                                                                                                                                            {
                                                                                                                                                  m_table[i][j] = -1;
                                                                                                                                                        s_table[i][j] = -1;
                                                                                                                                                              }
                                                                                                                                                                }


                                                                                                                                                                ///////////////////////////////////////////////////////////////

                                                                                                                                                                void matrix_chain_order(int p[], int i_start, int i_end, 
                                                                                                                                                                  int &m, int &s)
                                                                                                                                                                    {
                                                                                                                                                                      int cost1;
                                                                                                                                                                        int cost2;
                                                                                                                                                                          int i;
                                                                                                                                                                            int j;
                                                                                                                                                                              int k;
                                                                                                                                                                                int total_cost;
                                                                                                                                                                                  int s1;
                                                                                                                                                                                    int s2;
                                                                                                                                                                                      int last;

                                                                                                                                                                                        if (m_table[i_start][i_end] >= 0)
                                                                                                                                                                                            {
                                                                                                                                                                                                m = m_table[i_start][i_end];
                                                                                                                                                                                                    s = s_table[i_start][i_end];
                                                                                                                                                                                                        return;
                                                                                                                                                                                                            }

                                                                                                                                                                                                              m = 999999999;
                                                                                                                                                                                                                s = -1;

                                                                                                                                                                                                                  for (last = i_start; last < i_end; last++)
                                                                                                                                                                                                                     {
                                                                                                                                                                                                                          matrix_chain_order(p, i_start, last, cost1, s1);
                                                                                                                                                                                                                              matrix_chain_order(p, last + 1, i_end, cost2, s2);
                                                                                                                                                                                                                                  total_cost = cost1 + cost2 + p[i_start-1] * p[last] * p[i_end];
                                                                                                                                                                                                                                      if (total_cost < m)
                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                  m = total_cost;
                                                                                                                                                                                                                                                        s = last;
                                                                                                                                                                                                                                                              }  // if total_cost < m
                                                                                                                                                                                                                                                                  }  // for last

                                                                                                                                                                                                                                                                    // put values in tables before returning
                                                                                                                                                                                                                                                                      m_table[i_start][i_end] = m;
                                                                                                                                                                                                                                                                        s_table[i_start][i_end] = s;
                                                                                                                                                                                                                                                                          }

                                                                                                                                                                                                                                                                          ///////////////////////////////////////////////////////////////

                                                                                                                                                                                                                                                                          int main()
                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                              int m;

                                                                                                                                                                                                                                                                              //Example from page 337 in text
                                                                                                                                                                                                                                                                              //int n = 6;
                                                                                                                                                                                                                                                                              //int p[MAX] = {30, 35, 15, 5, 10, 20, 25};

                                                                                                                                                                                                                                                                              //Example with small numbers of easy check by hand
                                                                                                                                                                                                                                                                              //int n = 5;
                                                                                                                                                                                                                                                                              //int p[MAX] = {3, 2, 5, 4, 2, 3};
                                                                                                                                                                                                                                                                              //int s;

                                                                                                                                                                                                                                                                              //Example with large n to test speed
                                                                                                                                                                                                                                                                              //Extra values in p so that n can be made larger if desired
                                                                                                                                                                                                                                                                              //int n = 19;
                                                                                                                                                                                                                                                                              //int p[MAX] = { 3, 92,  5,  4, 92, 83,  7,  5,  3,  6, 
                                                                                                                                                                                                                                                                              //              15, 24, 36, 52, 76, 24,  3,  2, 52,  4, 
                                                                                                                                                                                                                                                                              //               2,  3,  7,  5,  3,  6,  5,  2,  6,  2, 
                                                                                                                                                                                                                                                                              //               6};

                                                                                                                                                                                                                                                                              //Example from practice test 1, 2015
                                                                                                                                                                                                                                                                                int n = 5;
                                                                                                                                                                                                                                                                                  int p[MAX] = {5, 6, 2, 3, 4, 3};
                                                                                                                                                                                                                                                                                    int s;

                                                                                                                                                                                                                                                                                      init_tables(n);
                                                                                                                                                                                                                                                                                        matrix_chain_order(p, 1, n, m, s); 
                                                                                                                                                                                                                                                                                          cout << "m = " << m << ", s = " << s << endl;
                                                                                                                                                                                                                                                                                            print_tables(n);
                                                                                                                                                                                                                                                                                              }

                                                                                                                                                                                                                                                                                              ///////////////////////////////////////////////////////////////
