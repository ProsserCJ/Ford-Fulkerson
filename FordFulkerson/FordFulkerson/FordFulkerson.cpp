/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"
#include <queue>
using std::queue;

FordFulkerson::FordFulkerson(char* input) : graph(DiGraph(input)) {

}

void FordFulkerson::run(int source, int sink) {
	vector<vector<Node> > paths = findAllAugmentingPaths();
	for(int i=0; i<paths.size(); ++i) {

	}
}

void FordFulkerson::print() {

}

//using depth-first search
vector<vector<Node> > FordFulkerson::findAllAugmentingPaths() {
	vector<vector<Node> > allPaths;

	//find source node 
	Node* sourceNode;
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

	return allPaths;
}