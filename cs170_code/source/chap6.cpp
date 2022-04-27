#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "../include/chap6.h"
#include "../include/tree.h"

// [1:i]
int longest_increasing_subsequence(vector<int>& nums) {
	int n = nums.size();
	int* dp = new int[n-1]; 
	for (int i = 0; i < n; ++i) {
		dp[i] = 1;
	}
	int res = 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if(nums[j] < nums[i]) dp[i] = max(dp[i], 1 + dp[j]);
		}
		res = max(res, dp[i]);
	}
	return res;
}

// [1:i]
int cut_rod_helper(int n, int* dp, vector<int>& prices) {
	if (n == 0) return 0;
	if (dp[n] >= 0) return dp[n];
	int res = INT_MIN;
	for (int i = 1; i <= n; ++i) res = max(res, prices[i - 1] + cut_rod_helper(n - i, dp, prices));
	dp[n] = res;
	return res;

}

int cut_rod(int n, vector<int>& prices) {
	int* dp = new int[n + 1];
	for (int i = 1; i <= n; ++i) dp[i] = INT_MIN;
	return cut_rod_helper(n, dp, prices);
}

// [i:j]
int matrix_chain(vector<int>& m) {
	int n = m.size() - 1;
	int** dp = new int*[n + 1];
	for (int i = 0; i <= n; ++i) dp[i] = new int[n + 1];
	for (int i = 1; i <= n; ++i) dp[i][i] = 0;
	for (int z = 1; z <= n - 1; ++z) {
		for (int i = 1; i <= n - z; ++i) {
			int j = i + z;
			dp[i][j] = INT_MAX;
			for (int k = i; k < j; ++k) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + m[i - 1] * m[k] * m[j]);
			}
		}
	}
	return dp[1][n];
}

// [1:i] [1:j]
int longest_common_subsequence(string s1, string s2) {
	int m = s1.size();
	int n = s2.size();
	int** dp = new int* [m + 1];
	for (int i = 0; i <= m; ++i) dp[i] = new int[n + 1];
	for (int i = 0; i <= m; ++i) dp[i][0] = 0;
	for (int j = 0; j <= n; ++j) dp[0][j] = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s1[i] == s2[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[m][n];
}

// [1:i] [1:j]
int minimum_edit_distance(string s1, string s2) {
	int m = s1.size();
	int n = s2.size();
	int** dp = new int* [m + 1];
	for (int i = 0; i <= m; ++i) dp[i] = new int[n + 1];
	for (int i = 0; i <= m; ++i) dp[i][0] = i;
	for (int j = 0; j <= n; ++j) dp[0][j] = j;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s1[i] == s2[j]) dp[i][j] = dp[i - 1][j - 1];
			else dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);
		}
	}
	return dp[m][n];
}

// [1:i] [1:j]
int knapsack_01(int W, vector<int>& weights, vector<int>& values) {
	int n = weights.size();
	int** dp = new int* [W + 1];
	for (int i = 0; i <= W; ++i) dp[i] = new int[n + 1];
	for (int i = 0; i <= W; ++i) dp[i][0] = 0;
	for (int j = 0; j <= n; ++j) dp[0][j] = 0;
	for (int j = 1; j <= n; ++j) {
		for (int w = 1; w <= W; ++w) {
			if (weights[j - 1] > w) dp[w][j] = dp[w][j - 1];
			else dp[w][j] = max(dp[w][j - 1], dp[w - weights[j-1]][j-1]+values[j-1]);
		}
	}
	return dp[W][n];
}

// [1:i]
int knapsack_unbounded(int W, vector<int>& weights, vector<int>& values) {
	int n = weights.size();
	int* dp = new int[W + 1]; dp[0] = 0;
	for (int w = 1; w <= W; ++w) {
		dp[w] = 0;
		for (int i = 0; i < n; ++i) {
			if (weights[i] <= w) dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
		}
	}
	return dp[W];
}

int knapsack_bounded(int W, vector<int>& weights, vector<int>& values, vector<int>& nums) {
	int n = weights.size();
	int** dp = new int* [W + 1];
	for (int i = 0; i <= W; ++i) dp[i] = new int[n + 1];
	for (int i = 0; i <= W; ++i) dp[i][0] = 0;
	for (int j = 0; j <= n; ++j) dp[0][j] = 0;
	for (int j = 1; j <= n; ++j) {
		for (int w = 1; w <= W; ++w) {
			int K = min(nums[j - 1], (int)(w * 1.0 / weights[j - 1]));
			dp[w][j] = INT_MIN;
			for (int k = 0; k <= K; ++k) {
				dp[w][j] = max(dp[w][j], dp[w - k*weights[j - 1]][j - 1] + k*values[j - 1]);
			}
		}
	}
	return dp[W][n];
}


class KnapsackItem {
public:
	float weight;
	float value;
	KnapsackItem(float weight, float value): weight(weight), value(value){}
};

bool knapsack_fractional_cmp(KnapsackItem item1, KnapsackItem item2) {
	return item1.value / item1.weight > item2.value / item2.weight;
}

// greedy
float knapsack_fractional(float W, vector<float>& weights, vector<float>& values) {
	int n = weights.size();
	vector<KnapsackItem> knapsack_items;
	for (int i = 0; i < n; ++i) {
		knapsack_items.push_back(KnapsackItem(weights[i], values[i]));
	}
	sort(knapsack_items.begin(), knapsack_items.end(), knapsack_fractional_cmp);
	float profit = 0.0;
	for (int i = 0; i < n && W > 0; ++i) {
		float w = min(W, knapsack_items[i].weight);
		W -= w;
		profit += w * (knapsack_items[i].value / knapsack_items[i].weight);
	}
	return profit;
}


int independent_sets_in_tree_helper(TreeNode<char>* root, unordered_map<TreeNode<char>*, int>& dp) {
	if (dp.find(root) != dp.end()) return dp[root];
	vector<TreeNode<char>*> children = root->children;
	if (children.size() == 0) return 1;
	int sum_children = 0;
	int sum_grandchildren = 0;
	for (TreeNode<char>* child : children) {
		sum_children += independent_sets_in_tree_helper(child, dp);
		vector<TreeNode<char>*> grandchildren = child->children;
		for (TreeNode<char>* grandchild : grandchildren) {
			sum_grandchildren += independent_sets_in_tree_helper(grandchild, dp);
		}
	}
	dp[root] = max(1 + sum_grandchildren, sum_children);
	return dp[root];
}

int independent_sets_in_tree(TreeNode<char>* root) {
	unordered_map<TreeNode<char>*, int> dp;
	return independent_sets_in_tree_helper(root, dp);
}