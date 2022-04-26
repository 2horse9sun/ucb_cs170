#pragma once
#ifndef chap5_
#define chap5_

#include <iostream>
#include <vector>
#include <map>
#include "./vertex.h"
#include "./edge.h"
#include "./graph.h"
#include "./tree_node.h"
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

template<class T>
class HuffmanNode : public TreeNode<T> {
public:
	int freq;
	HuffmanNode(T element, int freq, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr)
		: TreeNode<T>(element, left, right){
		this->freq = freq;
	}
};

unordered_map<char, string> huffman(vector<char> chs, unordered_map<char, int> freqs);
void huffman_test();

// starting & finishing time of activities
vector<vector<int>> greedy_activity_selector(vector<vector<int>> sf_time);
void greedy_activity_selector_test();

#endif // !chap5_

