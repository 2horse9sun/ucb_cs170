#pragma once
#ifndef chap5_
#define chap5_

#include <iostream>
#include "./vertex.h"
#include "./edge.h"
#include "./graph.h"
using namespace std;

void makeset(Vertex* x);
Vertex* find(Vertex* x);
void unionset(Vertex* x, Vertex* y);

vector<Edge*> kruskal(Graph G);
void print_kruskal(Graph G);
void kruskal_test();
vector<Edge*> prim(Graph G);
void print_prim(Graph G);
void prim_test();


#endif // !chap5_

