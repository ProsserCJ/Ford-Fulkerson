/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include <iostream>
#include <fstream>
#include <vector>
using std::vector;

struct Node {
	Node(int num) {
		this->num = num;
	};
	int num;
};

class DiGraph {
public:
	DiGraph(char* input) {}

};

class FordFulkerson{
public:
	/**
		Constructs a digraph to run the Ford Fulkerson algorithm on

		@param input
			the path of a text file in which the digraph is specified
	*/
	FordFulkerson(char* input);

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
	vector<vector<Node> > findAllAugmentingPaths();

	DiGraph graph;
	int source, sink;

};
