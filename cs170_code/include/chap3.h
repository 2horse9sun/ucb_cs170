#pragma once
#ifndef chap3_
#define chap3_

#include <iostream>
#include "./vertex.h"
#include "./edge.h"
#include "./graph.h"
using namespace std;

void undirected_graph_test();

void explore(Graph G, Vertex* v);
void previsit(Vertex* v);
void postvisit(Vertex* v);
void dfs(Graph G);
void dfs_test();

void print_undirected_cc(Graph G);
void undirected_cc_test();

void print_dag_topological_sort(Graph G);
void dag_topological_sort_test();

void print_directed_scc(Graph G);
void directed_scc_test();

#endif // !chap3_

