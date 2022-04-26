#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>

#include "../include/chap3.h"
#include "../include/chap4.h"
#include "../include/chap5.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"
#include "../include/tree_node.h"

extern unordered_map<Vertex*, bool> visited;
extern unordered_map<Vertex*, Vertex*> parent;
unordered_map<Vertex*, int> ranks;

unordered_map<Vertex*, int> cost;


class prim_cmp {
public:
	bool operator()(Vertex* v1, Vertex* v2) const {
		return cost[v1] < cost[v2];
	}
};

multiset<Vertex*, prim_cmp> prim_queue;

void makeset(Vertex* x) {
	parent[x] = x;
	ranks[x] = 0;
}

Vertex* find(Vertex* x) {
	if (parent[x] != x) parent[x] = find(parent[x]);
	return parent[x];
}

void unionset(Vertex* x, Vertex* y) {
	Vertex* rx = find(x);
	Vertex* ry = find(y);
	if (rx == ry) return;
	if (ranks[rx] > ranks[ry]) {
		parent[ry] = rx;
	} 
	else {
		parent[rx] = ry;
		if (ranks[rx] == ranks[ry]) ranks[ry] = ranks[ry] + 1;
	}
}

class weight_cmp {
public:
	bool operator()(Edge* e1, Edge* e2) {
		return e1->get_weight() > e2->get_weight();
	}
};

vector<Edge*> kruskal(Graph G) {
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		makeset(*iter);
	}

	vector<Edge*> mst_edges;
	priority_queue<Edge*, vector<Edge*>, weight_cmp> q;
	unordered_set<Edge*> edges = G.get_edge_set();
	for (auto iter = edges.begin(); iter != edges.end(); iter++) {
		q.push(*iter);
	}
	while (!q.empty()) {
		Edge* e = q.top(); q.pop();
		
		Vertex* u = e->get_first_vertex();
		Vertex* v = e->get_second_vertex();
		if (find(u) != find(v)) {
			mst_edges.push_back(e);
			unionset(u, v);
		}
	}
	
	return mst_edges;
}

void print_kruskal(Graph G) {
	vector<Edge*> mst_edges = kruskal(G);
	for (auto iter = mst_edges.begin(); iter != mst_edges.end(); iter++) {
		cout << (*iter)->to_string() << endl;
	}
}

vector<Edge*> prim(Graph G) {
	unordered_set<Vertex*> vertices = G.get_vertex_set();
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		cost[*iter] = INT_MAX;
	}
	Vertex* r = *vertices.begin();
	cost[r] = 0;

	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		prim_queue.insert(*iter);
	}

	while (!prim_queue.empty()) {
		Vertex* v = *prim_queue.begin(); prim_queue.erase(prim_queue.begin());
		visited[v] = true;
		vector<Edge*> edges = G.get_adj_edges(v);
		for (auto iter = edges.begin(); iter != edges.end(); iter++) {
			Edge* e = *iter;
			Vertex* z = e->get_second_vertex();
			if ((prim_queue.find(z) != prim_queue.end()) && cost[z] > e->get_weight()) {
				cost[z] = e->get_weight();
				parent[z] = v;
				if (prim_queue.find(z) != prim_queue.end()) {
					prim_queue.erase(prim_queue.find(z));
					prim_queue.insert(z);
				}
			}
		}
	}

	vector<Edge*> mst_edges;
	for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
		Vertex* v = *iter;
		if (parent.find(v) != parent.end()) {
			mst_edges.push_back(G.get_edge(v, parent[v]));
		}
	}

	return mst_edges;
}

void print_prim(Graph G) {
	vector<Edge*> mst_edges = prim(G);
	for (auto iter = mst_edges.begin(); iter != mst_edges.end(); iter++) {
		cout << (*iter)->to_string() << endl;
	}
}

class huffman_cmp {
public:
	bool operator()(HuffmanNode<char>* n1, HuffmanNode<char>* n2) {
		return n1->freq > n2->freq;
	}
};

void compute_code_map(TreeNode<char>* root, unordered_map<char, string>& code_map, string str) {
	if (root->left == nullptr && root->right == nullptr) {
		code_map[root->element] = str;
	}
	else {
		compute_code_map(root->left, code_map, str + "0");
		compute_code_map(root->right, code_map, str + "1");
	}
}

unordered_map<char, string> huffman(vector<char> chs, unordered_map<char, int> freqs) {
	int n = chs.size();
	priority_queue<HuffmanNode<char>*, vector<HuffmanNode<char>*>, huffman_cmp> q;
	for (char ch : chs) {
		q.push(new HuffmanNode<char>(ch, freqs[ch]));
	}
	for (int i = 0; i < n - 1; ++i) {
		HuffmanNode<char>* left_node = q.top(); q.pop();
		HuffmanNode<char>* right_node = q.top(); q.pop();
		q.push(new HuffmanNode<char>(' ', left_node->freq + right_node->freq, left_node, right_node));
	}
	HuffmanNode<char>* root = q.top();
	unordered_map<char, string> code_map;
	string str = "";
	compute_code_map(root, code_map, str);
	return code_map;
}



bool activity_cmp(vector<int> v1, vector<int> v2) {
	return v1[1] < v2[1];
}

vector<vector<int>> greedy_activity_selector(vector<vector<int>> sf_time) {
	sort(sf_time.begin(), sf_time.end(), activity_cmp);
	int n = sf_time.size();
	vector<vector<int>> arrangement;
	arrangement.push_back(sf_time[0]);
	int k = 0;
	for (int i = 1; i < n; ++i) {
		if (sf_time[i][0] >= sf_time[k][1]) {
			arrangement.push_back(sf_time[i]);
			k = i;
		}
	}
	return arrangement;
}