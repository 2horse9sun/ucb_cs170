#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"

using namespace std;

Graph::Graph() {
	this->vertices = unordered_set<Vertex*>();
	this->edges = unordered_set<Edge*>();
	this->adj_list = unordered_map<Vertex*, vector<Edge*>>();
}

bool Graph::has_vertex(Vertex* v) {
	return this->vertices.find(v) != this->vertices.end();
}

void Graph::add_vertex(Vertex* v) {
	if (!this->has_vertex(v)) {
		this->vertices.insert(v);
		this->adj_list.insert({ v, vector<Edge*>() });
	}
}

void Graph::remove_vertex(Vertex* v) {
	if (this->has_vertex(v)) {
		vector<Edge*> removed_edges;
		for (auto iter = this->edges.begin(); iter != this->edges.end(); iter++) {
			if ((*iter)->get_first_vertex() == v || (*iter)->get_second_vertex() == v) {
				removed_edges.push_back((*iter));
			}
		}
		for (int i = 0; i < removed_edges.size(); ++i) {
			Edge* e = removed_edges[i];
			if (this->has_edge(e)) {
				Vertex* v1 = e->get_first_vertex();
				this->adj_list[v1].erase(find(this->adj_list[v1].begin(), this->adj_list[v1].end(), e));
				this->edges.erase(e);
			}
		}
		this->vertices.erase(v);
	}
}

bool Graph::has_edge(Edge* e) {
	return this->edges.find(e) != this->edges.end();
}

void Graph::add_edge(Edge* e) {
	if (!this->has_edge(e)) {

		this->edges.insert(e);

		Vertex* v1 = e->get_first_vertex();
		Vertex* v2 = e->get_second_vertex();
		if (!this->has_vertex(v1)) this->add_vertex(v1);
		if (!this->has_vertex(v2)) this->add_vertex(v2);

		if (find(this->adj_list[v1].begin(), this->adj_list[v1].end(), e) == this->adj_list[v1].end()) {
			this->adj_list[v1].push_back(e);
		}
	}
}

void Graph::remove_edge(Edge* e) {
	if (this->has_edge(e)) {
		Vertex* v1 = e->get_first_vertex();
		this->adj_list[v1].erase(find(this->adj_list[v1].begin(), this->adj_list[v1].end(), e));
		this->edges.erase(e);
	}
}

unordered_set<Vertex*> Graph::get_vertex_set() {
	return this->vertices;
}

unordered_set<Edge*> Graph::get_edge_set() {
	return this->edges;
}

void Graph::print_vertices() {
	vector<string> res;
	for (auto iter = this->vertices.begin(); iter != this->vertices.end(); iter++) {
		res.push_back((*iter)->to_string());
	}
	for (int i = 0; i < res.size(); ++i) {
		if (i == res.size() - 1) cout << res[i];
		else cout << res[i] << ",";
	}
}

void Graph::print_edges() {
	vector<string> res;
	for (auto iter = this->edges.begin(); iter != this->edges.end(); iter++) {
		res.push_back((*iter)->to_string());
	}
	for (int i = 0; i < res.size(); ++i) {
		if (i == res.size() - 1) cout << res[i];
		else cout << res[i] << ",";
	}
}

vector<Vertex*> Graph::get_neighbours(Vertex* v) {
	vector<Edge*> adj_edges = this->adj_list[v];
	vector<Vertex*> adj_vertices;
	for (Edge* e : adj_edges) {
		adj_vertices.push_back(e->get_second_vertex());
	}
	return adj_vertices;
}

void Graph::print_neighbours(Vertex* v) {
	vector<Vertex*> adj_vertices = this->get_neighbours(v);
	for (int i = 0; i < adj_vertices.size(); ++i) {
		if (i == adj_vertices.size() - 1) cout << adj_vertices[i]->to_string();
		else cout << adj_vertices[i]->to_string() << ",";
	}
}
