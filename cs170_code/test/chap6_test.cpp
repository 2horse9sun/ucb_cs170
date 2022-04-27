#include <iostream>
#include <time.h>
#include <vector>
#include <string>

#include "../include/chap6.h"
#include "../include/tree.h"


void LIS_test() {

    std::cout << "LIS_test" << std::endl;

    clock_t start, end;
    start = clock();

    vector<int> nums = { 5, 2, 8, 6, 3, 6, 9, 7 };
    cout << "Length of LIS: " << longest_increasing_subsequence(nums) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void cut_rod_test() {

    std::cout << "cut_rod_test" << std::endl;

    clock_t start, end;
    start = clock();

    vector<int> prices = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    cout << "Max profit: " << cut_rod(8, prices) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void matrix_chain_test() {

    std::cout << "matrix_chain_test" << std::endl;

    clock_t start, end;
    start = clock();

    vector<int> m = { 50, 20, 1, 10, 100};
    cout << "Min cost: " << matrix_chain(m) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void LCS_test() {

    std::cout << "LCS_test" << std::endl;

    clock_t start, end;
    start = clock();

    string s1 = "ABCBDAB";
    string s2 = "BDCABA";
    cout << "LCS: " << longest_common_subsequence(s1, s2) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void MED_test() {

    std::cout << "MED_test" << std::endl;

    clock_t start, end;
    start = clock();

    string s1 = "EXPONENTIAL";
    string s2 = "POLYNOMIAL";
    cout << "MED: " << minimum_edit_distance(s1, s2) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void knapsack_01_test() {

    std::cout << "knapsack_01_test" << std::endl;

    clock_t start, end;
    start = clock();
    int W = 10;
    vector<int> weights = { 6, 3, 4, 2 };
    vector<int> values = { 30, 14, 16, 9 };
    cout << "Max profit: " << knapsack_01(W, weights, values) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void knapsack_unbounded_test() {

    std::cout << "knapsack_unbounded_test" << std::endl;

    clock_t start, end;
    start = clock();
    int W = 10;
    vector<int> weights = { 6, 3, 4, 2 };
    vector<int> values = { 30, 14, 16, 9 };
    cout << "Max profit: " << knapsack_unbounded(W, weights, values) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void knapsack_bounded_test() {

    std::cout << "knapsack_bounded_test" << std::endl;

    clock_t start, end;
    start = clock();
    int W = 10;
    vector<int> weights = { 6, 3, 4, 2 };
    vector<int> values = { 30, 14, 16, 9 };
    vector<int> nums = { 10, 10, 10, 10 };
    cout << "Max profit: " << knapsack_bounded(W, weights, values, nums) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void knapsack_fractional_test() {

    std::cout << "knapsack_fractional_test" << std::endl;

    clock_t start, end;
    start = clock();
    float W = 50.0;
    vector<float> weights = { 10.0, 20.0, 30.0 };
    vector<float> values = { 60.0, 100.0, 120.0 };
    cout << "Max profit: " << knapsack_fractional(W, weights, values) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void independent_sets_in_tree_test() {

    std::cout << "independent_sets_in_tree_test" << std::endl;

    clock_t start, end;
    start = clock();
    
    TreeNode<char>* F = new TreeNode<char>('F');
    TreeNode<char>* G = new TreeNode<char>('G');
    TreeNode<char>* H = new TreeNode<char>('H');
    TreeNode<char>* I = new TreeNode<char>('I');
    TreeNode<char>* C = new TreeNode<char>('C', {F, G});
    TreeNode<char>* D = new TreeNode<char>('D');
    TreeNode<char>* E = new TreeNode<char>('E', { H, I });
    TreeNode<char>* B = new TreeNode<char>('B', { C, D, E });
    TreeNode<char>* A = new TreeNode<char>('A', { B });

    cout << "Max num of independent sets in tree: " << independent_sets_in_tree(A) << endl;


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}