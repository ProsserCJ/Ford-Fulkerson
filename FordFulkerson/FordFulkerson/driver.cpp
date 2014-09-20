/*	Chris Prosser, Eric Weaver, Laura Wendlendt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"

int main()
{
	FordFulkerson ff("input.txt");
	ff.run();
	ff.print();

	return 0;
}