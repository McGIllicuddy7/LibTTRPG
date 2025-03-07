#include "AStar.h"
//https://en.wikipedia.org/wiki/A*_search_algorithm

struct AStarInternalNode_t{
	int idx;
	std::vector<int> edges;
	std::vector<double> edge_distances;
	//heuristic function
	double h;
	//cost from the start of the path to the node
	double g;
	double f()const {
		return h+g;
	}
	bool operator ==(AStarInternalNode_t other)const {
		return other.idx == this->idx;
	}
};
static int set_min(const std::vector<AStarInternalNode_t>& set){
	const double inf = 10e15;
	double minval = inf*2;
	double minidx = -1;
	//printf("set size: %zu\n", set.size());
	for(size_t i =0; i<set.size(); i++){
		if(set[i].f()<minval){
			minval = set[i].f();
			minidx =i;
		}
	}
	if(minidx == -1){
		exit(-1);
	}
	return minidx;
}
static std::vector<int> reconstruct_path(const std::vector<int>& camefrom, int current){
	std::vector<int> out = {};
	while(camefrom[current] != -1){
		out.push_back(current);
		current = camefrom[current];
	}
    out.push_back(current);
	return out;
}
void SetRemove(std::vector<int>& set, int index){
	set.erase(set.begin()+(index));
}
static bool SetContains(const std::vector<int>& set, int value){
	for(size_t i =0; i<set.size(); i++){
		if(set[i] == value){
			//printf("%d = %d\n", set[i].idx, value.idx);
			return true;
		}
	}
	//printf("set doesn't contain: %d\n",value.idx);
	return false;
}
std::vector<int> AStar(std::vector<AStarNode_t> in_nodes, int start, int end){
    int start_tmp = start;
    start = end;
    end = start_tmp;
	std::vector<AStarInternalNode_t> nodes = {};
	//set up
	const double inf = 10e15;
	nodes.reserve(in_nodes.size());
	for(size_t i =0; i<in_nodes.size(); i++){
		AStarInternalNode_t node;
		node.idx = i;
		node.edges = in_nodes[i].edges;
		node.edge_distances = in_nodes[i].distances;
		node.g = inf;
		node.h = in_nodes[i].euc_distance;
		nodes.push_back(node);
	}
	nodes[start].g = 0;
	//end set up 
	std::vector<int> openset = {start};
	std::vector<int> camefrom = {};
	//camefrom set up;
	camefrom.reserve(nodes.size());
	for(size_t i =0; i<nodes.size(); i++){
		camefrom.push_back(-1);
	}
	//end camefrom set up
	std::vector<double> fscore = {};
	//fscore set up
	fscore.reserve(nodes.size());
	for(size_t i = 0; i<nodes.size(); i++){
		fscore.push_back(inf);
	}
	fscore[start] = nodes[start].h;
	//end fscore set up
	std::vector<AStarInternalNode_t> tmp = {};
	tmp.reserve(openset.size());
	while(openset.size()>0){
		tmp.clear();
		for(size_t i =0; i<openset.size(); i++){
			tmp.push_back(nodes[openset[i]]);
		}
		int crtmp = set_min(tmp);
		int current = openset[crtmp];
		if(current == end){
			return reconstruct_path(camefrom, current);
		}
	 	SetRemove(openset, crtmp);
		for(size_t i =0; i<nodes[current].edges.size(); i++){
			int neighbor = nodes[current].edges[i];
			double tmp_g_score = nodes[current].g+nodes[current].edge_distances[i];
			if(tmp_g_score<nodes[neighbor].g){
				camefrom[neighbor] = current;
				nodes[neighbor].g = tmp_g_score;
				if(!SetContains(openset, neighbor)){
					openset.push_back(neighbor);
				}
			}
		}
	}
	return {};
}
