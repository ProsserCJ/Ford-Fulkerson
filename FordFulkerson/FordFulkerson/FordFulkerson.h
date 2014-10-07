/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#ifndef __FORD_FULKERSON_H
#define __FORD_FULKERSON_H

#include "DiGraph.h"
#include <vector>
using std::vector;

class FordFulkerson{
public:
	/**
		Constructs a digraph to run the Ford Fulkerson algorithm on

		@param input
			the string of characters in which the digraph is specified
	*/
	FordFulkerson(char* input) : graph(DiGraph(input)) {}

	/**
		Constructs a digraph to run the Ford Fulkerson algorithm on

		@param input
			the string of characters in which the digraph is specified
		@param simple
			the presence of this boolean indicates using a different method of input in constructing the digraph
	*/
	FordFulkerson(char* input, bool simple) : graph(DiGraph(input, simple)) {}

	/**
		Run the Ford Fulkerson algorithm on the digraph, with flow going from the source to the sink

		@param source
			The number of the node where flow starts
		@param sink
			The number of the node where flow ends
	*/
	void run(int source, int sink);

	/**
		Print the results of the Ford Fulkerson algorithm on the digraph, including the capacities along each path
	*/
	void print();

private:
	vector<Node*> augmentedPath();

	DiGraph graph;
	int source, sink;
	int totalThroughput;	
};

#endif