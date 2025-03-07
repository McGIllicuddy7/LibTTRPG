#pragma once
#include <vector>
#include <iostream>
#include <time.h>
//send this to A star as the external implementation of A*
struct AStarNode_t{
	//the indices of the edges in the array
	std::vector<int> edges;
	//the distances between each edge and the node
	std::vector<double> distances;
	//the euclidian distance between the node and the end
	double euc_distance;
};
//implemtation of A* using sets, create an array of nodes and it will return an array of indices that connect the two points
//it will return an empty set if there is not viable path s
//source is https://en.wikipedia.org/wiki/A*_search_algorithm
std::vector<int> AStar(std::vector<AStarNode_t> in_nodes, int start, int end);