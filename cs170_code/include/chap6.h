#pragma once
#ifndef chap6_
#define chap6_

#include <iostream>
#include <string>
#include "./tree.h"
using namespace std;

int longest_increasing_subsequence(vector<int>& nums);
int cut_rod(int n, vector<int>& prices);
int matrix_chain(vector<int>& m);
int longest_common_subsequence(string s1, string s2);
int minimum_edit_distance(string s1, string s2);
int knapsack_01(int W, vector<int>& weights, vector<int>& values);
int knapsack_unbounded(int W, vector<int>& weights, vector<int>& values);
int knapsack_bounded(int W, vector<int>& weights, vector<int>& values, vector<int>& nums);
float knapsack_fractional(float W, vector<float>& weights, vector<float>& values);
int independent_sets_in_tree(TreeNode<char>* root);

void LIS_test();
void cut_rod_test();
void matrix_chain_test();
void LCS_test();
void MED_test();
void knapsack_01_test();
void knapsack_unbounded_test();
void knapsack_bounded_test();
void knapsack_fractional_test();
void independent_sets_in_tree_test();

#endif // !chap6_

