#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>


#include "../include/chap3.h"
#include "../include/chap4.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"

unordered_map<Vertex*, Vertex*> parent;
unordered_map<Vertex*, int> dist;


class dijkstra_cmp {
public:
	bool operator()(Vertex* v1, Vertex* v2) const {
		return dist[v1] < dist[v2];
	}
};



// used as a priority_queue with update_key function
multiset<Vertex*, dijkstra_cmp> dijkstra_queue;


void init_single_source(Graph G, Vertex* s) {
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		dist[*iter] = INT_MAX;
	}
	dist[s] = 0;
}

void relax(Edge* e) {
	Vertex* u = e->get_first_vertex();
	Vertex* v = e->get_second_vertex();
	if (dist[u] != INT_MAX && dist[v] > dist[u] + e->get_weight()) {
		dist[v] = dist[u] + e->get_weight();
		parent[v] = u;

		// for dijkstra
		if (dijkstra_queue.find(v) != dijkstra_queue.end()) {
			dijkstra_queue.erase(dijkstra_queue.find(v));
			dijkstra_queue.insert(v);
		}
		
	}
}

void bfs(Graph G, Vertex* s) {
	init_single_source(G, s);
	queue<Vertex*> q; q.push(s);
	while (!q.empty()) {
		Vertex* v = q.front(); q.pop();
		vector<Vertex*> vertices = G.get_adj_vertices(v);
		for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
			if (dist[*iter] == INT_MAX) {
				q.push(*iter);
				dist[*iter] = dist[v] + 1;
			}
		}
		cout << "dist[" << v->to_string() << "]=" << dist[v] << endl;
	}
}

bool bellman_ford(Graph G, Vertex* s) {
	init_single_source(G, s);
	// relax all edges |V|-1 times
	unordered_set<Edge*> edges = G.get_edge_set();
	for (int i = 0; i < G.get_vertex_set().size() - 1; ++i) {
		for (auto iter = edges.begin(); iter != edges.end(); iter++) {
			relax(*iter);
		}
	}

	// not stable => negative cycles
	for (auto iter = edges.begin(); iter != edges.end(); iter++) {
		Edge* e = *iter;
		Vertex* u = e->get_first_vertex();
		Vertex* v = e->get_second_vertex();
		if (dist[v] > dist[u] + e->get_weight()) {
			return false;
		}
	}

	return true;
}

void print_path(Vertex* s, Vertex* v) {
	int d = dist[v];
	stack<Vertex*> vertices;
	vertices.push(v);
	while (v != s) {
		if (parent.find(v) != parent.end()) {
			v = parent[v];
			vertices.push(v);
		} 
		else {
			cout << v->to_string() << " is unreachable from " << s->to_string() << endl;
			return;
		}
	}
	while (!vertices.empty()) {
		Vertex* u = vertices.top(); vertices.pop();
		if (vertices.empty()) {
			cout << u->to_string();
		}
		else {
			cout << u->to_string() << "->";
		}
	}
	cout << ": dist=" << d << endl;
}

void print_bellman_ford(Graph G, Vertex* s) {
	if (bellman_ford(G, s)) {
		unordered_set<Vertex*> vertices = G.get_vertex_set();
		for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
			print_path(s, *iter);
		}
	}
	else {
		cout << "Shortest path doesn't exist!" << endl;
	}
}

void dag_shortest_path(Graph G, Vertex* s) {
	init_single_source(G, s);
	// topological sort
	vector<Vertex*> vertices = dag_topological_sort(G);

	// relax all edges in topologically sorted order
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		Vertex* v = *iter;
		vector<Edge*> adj_edges = G.get_adj_edges(v);
		for (int i = 0; i < adj_edges.size(); ++i) {
			relax(adj_edges[i]);
		}
	}
}

void print_dag_shortest_path(Graph G, Vertex* s) {
	dag_shortest_path(G, s);
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		print_path(s, *iter);
	}
}



void dijkstra(Graph G, Vertex* s) {

	init_single_source(G, s);

	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		dijkstra_queue.insert(*iter);
	}

	while (!dijkstra_queue.empty()) {
		Vertex* v = *dijkstra_queue.begin(); dijkstra_queue.erase(dijkstra_queue.begin());
		vector<Edge*> edges = G.get_adj_edges(v);
		for (auto iter = edges.begin(); iter != edges.end(); iter++) {
			relax(*iter);
		}
	}
}

void print_dijkstra(Graph G, Vertex* s) {
	dijkstra(G, s);
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		print_path(s, *iter);
	}
}