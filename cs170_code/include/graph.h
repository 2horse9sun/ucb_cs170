#ifndef graph_
#define graph_
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "vertex.h"
#include "edge.h"

using namespace std;

class Graph {
public:
	unordered_set<Vertex*> vertices;
	unordered_set<Edge*> edges;
	unordered_map<Vertex*, vector<Edge*>> adj_list;


	Graph();

	bool has_vertex(Vertex* v);
	void add_vertex(Vertex* v);
	void remove_vertex(Vertex* v);
	bool has_edge(Edge* e);
	void add_edge(Edge* e);
	void remove_edge(Edge* e);
	Edge* get_edge(Vertex* v1, Vertex* v2);

	unordered_set<Vertex*> get_vertex_set();
	unordered_set<Edge*> get_edge_set();
	void print_vertices();
	void print_edges();
	vector<Vertex*> get_adj_vertices(Vertex* v);
	void print_adj_vertices(Vertex* v);
	vector<Edge*> get_adj_edges(Vertex* v);
	void print_adj_edges(Vertex* v);


};

#endif
