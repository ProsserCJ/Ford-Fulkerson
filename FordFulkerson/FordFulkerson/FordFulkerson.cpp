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

	vector<Node*> path = augmentedPath();
	while(path.size() != 0) {
		//calculate min flow among all the edges in the path
		int minFlow = -1;
		vector<Edge*> edgesInPath;
		for(int i=0; i<path.size()-1; ++i) {
			for(int j=0; j<graph.edges.size(); ++j) {
				if(graph.edges[j].start->num == path[i]->num && graph.edges[j].end->num == path[i+1]->num) { //forwards edge
					edgesInPath.push_back(&graph.edges[j]);
					int residualCapacity = graph.edges[j].capacity - graph.edges[j].throughPut;
					if(minFlow == -1 || residualCapacity < minFlow) {
						minFlow = residualCapacity;
					}
				} else if(graph.edges[j].end->num == path[i]->num && graph.edges[j].start->num == path[i+1]->num) { //backwards edge
					edgesInPath.push_back(&graph.edges[j]);
					if(minFlow == -1 || graph.edges[j].throughPut < minFlow) {
						minFlow = graph.edges[j].throughPut;
					}
				}
			}
		}

		//add the flow to all the edges
		for(int i=0; i<path.size()-1; ++i) {
			if(edgesInPath[i]->start->num == path[i]->num) { //forwards path
				edgesInPath[i]->throughPut += minFlow;
			} else { //backwards edge
				edgesInPath[i]->throughPut -= minFlow;
			}
		}

		//find the next augmented path
		path = augmentedPath();
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
	cout << setw(13) << "Node 1" << setw(13) << "Node 2" << setw(20) << "Flow / Capacity" << endl;
	for(int i=0; i<graph.edges.size(); ++i) {
		cout << setw(13) << graph.edges[i].start->num << setw(13) << graph.edges[i].end->num << setw(13) << graph.edges[i].throughPut
			<< " / " << graph.edges[i].capacity << endl;
	}
	cout << endl;
}

vector<Node*> FordFulkerson::augmentedPath() {
	struct SearchInfo {
		vector<Node*> startingPath;
		vector<bool> vertexInPath;
	};

	vector<bool> startingVertexInPath(graph.nodes.size(),false);
	vector<Node*> startingPath;
	startingPath.push_back(&graph.nodes[source]);
	startingVertexInPath[source] = true;

	queue<SearchInfo> horizon;
	SearchInfo startingInfo;
	startingInfo.startingPath = startingPath;
	startingInfo.vertexInPath = startingVertexInPath;
	horizon.push(startingInfo);

	while(!horizon.empty()) {
		SearchInfo top = horizon.front();
		horizon.pop();
		Node* lastNode = top.startingPath[top.startingPath.size()-1];

		if(lastNode->num == sink) {
			/*cout << "Path: ";
			for(int i=0; i<top.startingPath.size(); ++i) {
				cout << top.startingPath[i]->num << " ";
			}
			cout << endl;*/
			return top.startingPath;
		}

		//examine all adjacent edges
		for(int i=0; i<graph.edges.size(); ++i) {
			if(graph.edges[i].start->num == lastNode->num) { //forwards edge
				Node* endNode = graph.edges[i].end;
				int residualCapacity = graph.edges[i].capacity - graph.edges[i].throughPut;
				if(residualCapacity > 0 && top.vertexInPath[endNode->num] == false) {
					top.vertexInPath[endNode->num] = true;
					top.startingPath.push_back(endNode);
					horizon.push(top);
					top.vertexInPath[endNode->num] = false;
					top.startingPath.erase(top.startingPath.begin() + top.startingPath.size()-1);
				}
			} else if(graph.edges[i].end->num == lastNode->num) { //backwards edge
				Node* endNode = graph.edges[i].start;
				if(graph.edges[i].throughPut > 0 && top.vertexInPath[endNode->num] == false) {
					top.vertexInPath[endNode->num] = true;
					top.startingPath.push_back(endNode);
					horizon.push(top);
					top.vertexInPath[endNode->num] = false;
					top.startingPath.erase(top.startingPath.begin() + top.startingPath.size()-1);
				}
			}
		}
	}

	//cout << "No more augmenting paths" << endl;
	return vector<Node*>();
}