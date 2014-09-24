/*	Chris Prosser, Eric Weaver, Laura Wendlandt, Michael Wiegand
	COMP 422 -- Introduction to Algorithms, Project 1
	The Ford-Fulkerson algorithm for calculating max flow through a network
*/

#include "FordFulkerson.h"

FordFulkerson::FordFulkerson(char* input) : graph(DiGraph(input)) {

}

void FordFulkerson::run(int source, int sink) {
	vector<vector<Node> > paths = findAllAugmentingPaths();
	for(int i=0; i<paths.size(); ++i) {

	}
}

void FordFulkerson::print() {

}

vector<vector<Node> > FordFulkerson::findAllAugmentingPaths() {
	return vector<vector<Node> >(0, vector<Node>(0,0));
}