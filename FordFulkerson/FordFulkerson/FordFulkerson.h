/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include <iostream>
#include <fstream>
#include <sstream>
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
	DiGraph(char* input)
	{
		std::stringstream in(input);
		vector<float> capacites;
		int nodeCount = 0;
		while(!in.eof())
		{
			float c = 0;
			in >> c;
			capacites.push_back(c);
		}
		nodeCount = sqrt(capacites.size());
		for(int i(0); i < nodeCount; i++)
		{
			nodes.push_back(Node(i));
		}
		for(int i(0); i < capacites.size(); i++)
		{
			int start = static_cast<int>(i/nodeCount);
			int end = i%nodeCount;
			if(capacites[i] > 0 && start != end)
			{
				nodes[start].addEdge(&nodes[end], capacites[i]);
			}
		}
	}

	vector<Node> nodes;

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
