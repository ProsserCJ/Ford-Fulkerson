/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

int main()
{
	for(int i = 0; i < 5; ++i)
	{
		stringstream ss;
		string s;
		ss << "TestCases\\TestCase" << i << ".txt";
		ss >> s;
		ifstream fin(s);
		char a;
		string final = "";
		while(!fin.eof()) {
			fin.get(a);
			final += a;
		}
		char* cStr = (char*)final.c_str();
		FordFulkerson ff(cStr, true);

		ff.run(0,1);
		ff.print();
	}
	return 0;
}