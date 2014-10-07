/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "DiGraph.h"

#include <sstream>
#include <vector>
using std::vector;
using std::stringstream;

DiGraph::DiGraph(char* input)
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
	nodeCount = int(sqrt(float(capacites.size()))+.000001);
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
			edges.push_back(nodes[start].edges.at(nodes[start].edges.size()-1));
		}
	}
}

DiGraph::DiGraph(char* input, bool simple)
{
	std::stringstream in(input);
	int nodeCount = 0;
	in >> nodeCount;
	for(int i(0); i < nodeCount; i++)
	{
		nodes.push_back(Node(i));
	}
	while(!in.eof())
	{
		int start = 0;
		int end = 0;
		int size = 0;
		in >> start;
		in >> end;
		in >> size;
		nodes[start].addEdge(&nodes[end], size);
		edges.push_back(nodes[start].edges.at(nodes[start].edges.size()-1));
	}
}