/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"

int main()
{
	FordFulkerson ff("input.txt");
	ff.run(0,5);
	ff.print();

	return 0;
}