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

void FordFulkerson::run(int source, int sink) {
	this->source = source;
	this->sink = sink;

	//initialize throughPut in all edges to 0
	for(int i=0; i<graph.edges.size(); ++i) {
		graph.edges[i].throughPut = 0;
	}

	vector<Edge*> path = augmentedPath();
	while(path.size() != 0) {
		//calculate min flow among all the edges in the path
		int minFlow = -1;
		int currentNodeNumber = source;
		for(int i=0; i<path.size(); ++i) {
			if(path[i]->start->num == currentNodeNumber) { //forwards edge
				int residualCapacity = path[i]->capacity - path[i]->throughPut;
				if(minFlow == -1 || residualCapacity < minFlow) {
					minFlow = residualCapacity;
				}
				currentNodeNumber = path[i]->end->num;
			} else if(path[i]->end->num == currentNodeNumber) { //backwards edge
				if(minFlow == -1 || path[i]->throughPut < minFlow) {
					minFlow = path[i]->throughPut;
				}
				currentNodeNumber = path[i]->start->num;
			}
		}

		//add the flow to all the edges
		currentNodeNumber = source;
		for(int i=0; i<path.size(); ++i) {
			if(path[i]->start->num == currentNodeNumber) { //forwards path
				path[i]->throughPut += minFlow;
				currentNodeNumber = path[i]->end->num;
			} else { //backwards edge
				path[i]->throughPut -= minFlow;
				currentNodeNumber = path[i]->start->num;
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

void FordFulkerson::print(int startTime) {
	cout << "Edges: " << edgeCount() << " Nodes " << vertexCount() << "\n";
	cout << "Time: " << (clock() - startTime)/(double)CLOCKS_PER_SEC << " seconds.\n";
		
	cout << "Total throughput making it from source to sink: " << totalThroughput << endl << endl;
	cout << setw(13) << "Node 1" << setw(13) << "Node 2" << setw(20) << "Flow / Capacity" << endl;
	for(int i=0; i<graph.edges.size()-1; ++i) {
		cout << setw(13) << graph.edges[i].start->num << setw(13) << graph.edges[i].end->num << setw(13) << graph.edges[i].throughPut
			<< " / " << graph.edges[i].capacity << endl;
	}
	cout << endl;
}

vector<Edge*> FordFulkerson::augmentedPath() {
	struct SearchInfo {
		vector<Edge*> startingPath;
		vector<bool> vertexInPath;
		Node* lastNode;
	};

	vector<bool> startingVertexInPath(graph.nodes.size(),false);
	vector<Edge*> startingPath;
	startingVertexInPath[source] = true;

	queue<SearchInfo> horizon;
	SearchInfo startingInfo;
	startingInfo.startingPath = startingPath;
	startingInfo.vertexInPath = startingVertexInPath;
	startingInfo.lastNode = &graph.nodes[source];
	horizon.push(startingInfo);

	while(!horizon.empty()) {
		SearchInfo top = horizon.front();
		horizon.pop();

		if(top.lastNode->num == sink) {
			return top.startingPath;
		}

		Node* savedLastNode = top.lastNode;

		//examine all adjacent edges
		for(int i=0; i<graph.edges.size(); ++i) {
			if(graph.edges[i].start->num == top.lastNode->num) { //forwards edge
				Node* endNode = graph.edges[i].end;
				int residualCapacity = graph.edges[i].capacity - graph.edges[i].throughPut;
				if(residualCapacity > 0 && top.vertexInPath[endNode->num] == false) {
					top.vertexInPath[endNode->num] = true;
					top.startingPath.push_back(&graph.edges[i]);
					top.lastNode = &graph.nodes[graph.edges[i].end->num];
					horizon.push(top);
					top.vertexInPath[endNode->num] = false;
					top.startingPath.erase(top.startingPath.begin() + top.startingPath.size()-1);
					top.lastNode = savedLastNode;
				}
			} else if(graph.edges[i].end->num == top.lastNode->num) { //backwards edge
				Node* endNode = graph.edges[i].start;
				if(graph.edges[i].throughPut > 0 && top.vertexInPath[endNode->num] == false) {
					top.vertexInPath[endNode->num] = true;
					top.startingPath.push_back(&graph.edges[i]);
					top.lastNode = &graph.nodes[graph.edges[i].start->num];
					horizon.push(top);
					top.vertexInPath[endNode->num] = false;
					top.startingPath.erase(top.startingPath.begin() + top.startingPath.size()-1);
					top.lastNode = savedLastNode;
				}
			}
		}
	}

	return vector<Edge*>();
}