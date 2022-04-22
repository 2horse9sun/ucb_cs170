#pragma once
#ifndef chap4_
#define chap4_

#include <iostream>
#include "./vertex.h"
#include "./edge.h"
#include "./graph.h"
using namespace std;

void bfs(Graph G, Vertex* s);
void bfs_test();

bool bellman_ford(Graph G, Vertex* s);
void print_bellman_ford(Graph G, Vertex* s);
void bellman_ford_test();
void dag_shortest_path(Graph G, Vertex* s);
void print_dag_shortest_path(Graph G, Vertex* s);
void dag_shortest_path_test();
void dijkstra(Graph G, Vertex* s);
void print_dijkstra(Graph G, Vertex* s);
void dijkstra_test();

#endif // !chap4_

