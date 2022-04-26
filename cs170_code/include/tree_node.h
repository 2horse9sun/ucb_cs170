#ifndef tree_node_
#define tree_node_
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class T>
class TreeNode {
public:
	T element;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode(T element, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr)
		: element(element), left(left), right(right) {}


};

#endif
