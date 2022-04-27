#ifndef tree_
#define tree_
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class T>
class TreeNode {
public:
	T element;
	vector<TreeNode<T>*> children;

	TreeNode(T element, vector<TreeNode<T>*> children = vector<TreeNode<T>*>())
		: element(element), children(children) {}


};

template<class T>
class BSTNode {
public:
	T element;
	BSTNode<T>* left;
	BSTNode<T>* right;

	BSTNode(T element, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr)
		: element(element), left(left), right(right) {}


};

#endif
