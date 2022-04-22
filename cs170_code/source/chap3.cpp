#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "../include/chap3.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"

unordered_map<Vertex*, bool> visited;
int t = 0; // global clock
unordered_map<Vertex*, int> pre; // first time to visit v
unordered_map<Vertex*, int> post; // last time to visit v
unordered_map<Vertex*, int> post_tmp;

int group = 0; // connected components group number
unordered_map<Vertex*, int> cc; // connected components

vector<Vertex*> topological_sort_res;

void previsit(Vertex* v) {

	cout << v->to_string() << " ";

	pre[v] = t;
	t++;

	cc.insert({ v, group });

}

void postvisit(Vertex* v) {

	post[v] = t;
	t++;

	topological_sort_res.insert(topological_sort_res.begin(), v);
}


// find node reachable from v
void explore(Graph G, Vertex* v) {

	visited[v] = true;
	previsit(v);

	vector<Vertex*> neighbours = G.get_adj_vertices(v);
	for (auto iter = neighbours.begin(); iter != neighbours.end(); iter++) {
		if (!visited[*iter]) {
			explore(G, *iter);
		} 
	}

	postvisit(v);
}

void dfs(Graph G) {
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		visited[*iter] = false;
	}
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		if (!visited[*iter]) {
			explore(G, *iter);
			group++;
		} 
	}
}

void print_undirected_cc(Graph G) {
	dfs(G);
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	cout << endl;
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		cout << "cc group of vertex " << (*iter)->to_string() << ": " << cc[*iter] << endl;
	}
}

vector<Vertex*> dag_topological_sort(Graph G) {
	dfs(G);
	return topological_sort_res;
}

void print_dag_topological_sort(Graph G) {
	dfs(G);
	cout << endl;
	cout << "Topological sort: ";
	for (auto iter = topological_sort_res.begin(); iter != topological_sort_res.end(); iter++) {
		cout << (*iter)->to_string() << " ";
	}
	cout << endl;
}

class scc_cmp {
public:
	bool operator()(Vertex* v1, Vertex* v2) {
		return post_tmp[v1] < post_tmp[v2];
	}
};

void print_directed_scc(Graph G) {
	// run dfs on G_reverse
	Graph R = Graph();
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	unordered_set<Edge*> edges = G.get_edge_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		R.add_vertex(*iter);
	}
	for (auto iter = edges.begin(); iter != edges.end(); iter++) {
		Edge* reverse_edge = new Edge((*iter)->get_second_vertex(), (*iter)->get_first_vertex(), (*iter)->get_weight());
		R.add_edge(reverse_edge);
	}
	dfs(R);

	// run dfs on G, visiting vertices in DESC order of post[v]
	priority_queue<Vertex*, vector<Vertex*>, scc_cmp> pq;
	post_tmp = post;
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		pq.push(*iter);
	}

	visited.clear(); t = 0; pre.clear(); post.clear(); group = 0; cc.clear();

	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		visited[*iter] = false;
	}
	Vertex* v;
	while(!pq.empty()) {
		v = pq.top();
		pq.pop();
		if (!visited[v]) {
			explore(G, v);
			group++;
		}
	}

	// print
	cout << endl;
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		cout << "cc group of vertex " << (*iter)->to_string() << ": " << cc[*iter] << endl;
	}

	for (auto iter = R.edges.begin(); iter != R.edges.end(); iter++) {
		delete (*iter);
	}
}