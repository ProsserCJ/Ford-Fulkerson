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
	DiGraph(char* input);
	DiGraph(char* input, bool simple);

	vector<Node> nodes;
	vector<Edge> edges;
};

#endif