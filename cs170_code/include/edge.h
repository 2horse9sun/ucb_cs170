#ifndef edge_
#define edge_
#include <iostream>
#include <string>
#include <vector>

#include "vertex.h"

using namespace std;

class Edge {
public:
	Vertex* v1;
	Vertex* v2;
	int weight;

	Edge(Vertex* v1, Vertex* v2, int weight = 0): v1(v1), v2(v2), weight(weight) {}

	Vertex* get_first_vertex() {
		return v1;
	}
	Vertex* get_second_vertex() {
		return v2;
	}

	int get_weight() {
		return this->weight;
	}

	void update_weight(int w) {
		this->weight = w;
	}

	Edge reverse() {
		return Edge(v2, v1, weight);
	}

	string to_string() {
		return this->v1->name + "->" + this->v2->name;
	}

};

#endif
