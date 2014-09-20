/*	Chris Prosser, Eric Weaver, Laura Wendlendt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include <iostream>
#include <fstream>

class DiGraph {
public:
	DiGraph(char* input) {}

};

class FordFulkerson{
public:
	FordFulkerson(char* input): graph(DiGraph(input)){};
	void run(){}
	void print(){}

private:
	DiGraph graph;

};
