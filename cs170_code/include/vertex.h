#ifndef vertex_
#define vertex_
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vertex {
public:
	string name;

	Vertex(string name) : name(name) {}

	string to_string() {
		return this->name;
	}

};

#endif
