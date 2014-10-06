/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"
#include <queue>
#include <iostream>
#include <iomanip>
using std::setw;
using std::cout;
using std::endl;
using std::queue;

FordFulkerson::FordFulkerson(char* input) : graph(DiGraph(input)) {
}
FordFulkerson::FordFulkerson(char* input, bool simple) : graph(DiGraph(input,simple)) {
}

void FordFulkerson::run(int source, int sink) {
	this->source = source;
	this->sink = sink;

	//initialize throughPut in all edges to 0
	for(int i=0; i<graph.edges.size(); ++i) {
		graph.edges[i].throughPut = 0;
	}

	//search through all augmenting paths
	vector<vector<Node> > paths = findAllAugmentingPaths();
	for(int i=0; i<paths.size(); ++i) {
		int minPathCapacity = -1;
		vector<Edge*> edgesInPath;
		for(int j=0; j<paths[i].size()-1; ++j) {
			//find edge corresponding to nodes
			for(int k=0; k<graph.edges.size(); ++k) {
				if(graph.edges[k].start->num == paths[i][j].num && graph.edges[k].end->num == paths[i][j+1].num) {
					edgesInPath.push_back(&graph.edges[k]);
					if(minPathCapacity == -1 || (graph.edges[k].capacity - graph.edges[k].throughPut) < minPathCapacity) {
						minPathCapacity = graph.edges[k].capacity - graph.edges[k].throughPut;
					}
					break;
				}
			}
		}

		for(int k=0; k<edgesInPath.size(); ++k) {
			edgesInPath[k]->throughPut += minPathCapacity;
			for(int m=0; m<graph.edges.size(); ++m) {
				if(graph.edges[m].start->num == edgesInPath[k]->end->num && graph.edges[m].end->num == edgesInPath[k]->start->num) {
					graph.edges[m].throughPut -= minPathCapacity;
				}
			}
		}
	}

	//find all edges going into sink nodes, total throughput
	totalThroughput = 0;
	for(int i=0; i<graph.edges.size(); ++i) {
		if(graph.edges[i].end->num == sink) {
			totalThroughput += graph.edges[i].throughPut;
		}
	}
}

void FordFulkerson::print() {
	cout << "Total throughput making it from source to sink: " << totalThroughput << endl << endl;
	cout << setw(13) << "Node 1" << setw(13) << "Node 2" << setw(13) << "Throughput" << endl;
	for(int i=0; i<graph.edges.size(); ++i) {
		cout << setw(13) << graph.edges[i].start->num << setw(13) << graph.edges[i].end->num << setw(13) << graph.edges[i].throughPut << endl;
	}
	cout << endl;
}

//using depth-first search
vector<vector<Node> > FordFulkerson::findAllAugmentingPaths() {
	vector<vector<Node> > allPaths;

	//find source node 
	Node* sourceNode = NULL;
	for(int i=0; i<graph.nodes.size(); ++i) {
		if(graph.nodes[i].num == source) {
			sourceNode = &graph.nodes[i];
			break;
		}
	}

	queue<vector<Node> > horizon;
	vector<Node> startingPath;
	startingPath.push_back(*sourceNode);
	horizon.push(startingPath);

	while(!horizon.empty()) {
		vector<Node> top = horizon.front();
		horizon.pop();

		//push completed paths into returned vector
		if(top[top.size()-1].num == sink) {
			allPaths.push_back(top);
		} else {
			//for all the nodes adjacent to the last node in the path
			for(int i=0; i<top[top.size() - 1].edges.size(); ++i) {
				Edge e = top[top.size() - 1].edges[i];
				Node next = *(e.end);

				//check if the next node has already been visited
				bool visited = false;
				for(int j=0; j<top.size(); ++j) {
					if(top[j].num == next.num) {
						visited = true;
					}
				}
			
				if(!visited) {
					top.push_back(next);
					horizon.push(top);
					top.erase(top.begin()+top.size()-1);
				}
			}
		}
	}

	cout << "Augmenting paths:" << endl;
	for(int i=0; i<allPaths.size(); ++i) {
		for(int j=0; j<allPaths[i].size(); ++j) {
			cout << allPaths[i][j].num << " ";
		}
		cout << endl;
	}
	cout << endl;

	return allPaths;
}