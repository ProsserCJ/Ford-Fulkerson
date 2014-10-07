/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <vector>
using std::vector;

struct Node;
struct Edge;

struct Edge	{
	Edge(Node* start, Node* end, float capacity)
	{
		this->start = start;
		this->end = end;
		this->capacity = capacity;
		throughPut = 0;
	};
	Node* start;
	Node* end;
	float capacity;
	float throughPut;

};

struct Node {
	Node(int num) {
		this->num = num;
	};
	void addEdge(Node* a, float capacity)
	{
		edges.push_back(Edge(this, a, capacity));
	}
	int num;
	vector<Edge> edges;
};

class DiGraph {
public:
	/**
		Constructs a digraph from a given string of input

		@param input
			The string of input specifying information about the digraph. The information should be in the form of an n x n matrix,
			where there are n nodes in the graph. A 0 represents no edge between the nodes, and a number other than 0 represents a
			weighted edge between the nodes. Example:
				00001
				11001
				00001
				11100
				00000
	*/
	DiGraph(char* input);

	/**
		Constructs a digraph from a given string of input

		@param input
			The string of input specifying information about the digraph. The first line should contain the number of nodes, and
			each line after that should specify an edge (using three numbers: start node, end node, edge weight). Example:
				6
				0 1 10
				2 3 15
				0 3 25
	*/
	DiGraph(char* input, bool simple);

	vector<Node> nodes;
	vector<Edge> edges;
};

#endif