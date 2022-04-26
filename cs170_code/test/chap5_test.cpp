#include <iostream>
#include <time.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../include/chap5.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"

void kruskal_test() {
    // Fig 5.3
    Graph G53 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Edge AB(&A, &B, 2); Edge BA(&B, &A, 2);
    Edge AC(&A, &C, 1); Edge CA(&C, &A, 1);
    Edge BC(&B, &C, 2); Edge CB(&C, &B, 2);
    Edge BD(&B, &D, 1); Edge DB(&D, &B, 1);
    Edge CD(&C, &D, 2); Edge DC(&D, &C, 2);
    Edge CE(&C, &E, 3); Edge EC(&E, &C, 3);
    Edge DE(&D, &E, 3); Edge ED(&E, &D, 3);
    Edge DF(&D, &F, 4); Edge FD(&F, &D, 4);
    Edge EF(&E, &F, 1); Edge FE(&F, &E, 1);
    G53.add_vertex(&A); G53.add_vertex(&B); G53.add_vertex(&C); G53.add_vertex(&D); G53.add_vertex(&E); G53.add_vertex(&F);
    G53.add_edge(&AB); G53.add_edge(&BA);
    G53.add_edge(&AC); G53.add_edge(&CA);
    G53.add_edge(&BC); G53.add_edge(&CB);
    G53.add_edge(&BD); G53.add_edge(&DB);
    G53.add_edge(&CD); G53.add_edge(&DC);
    G53.add_edge(&CE); G53.add_edge(&EC);
    G53.add_edge(&DE); G53.add_edge(&ED);
    G53.add_edge(&DF); G53.add_edge(&FD);
    G53.add_edge(&EF); G53.add_edge(&FE);



    std::cout << "kruskal_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_kruskal(G53);

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void prim_test() {
    // Fig 5.3
    Graph G53 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Edge AB(&A, &B, 2); Edge BA(&B, &A, 2);
    Edge AC(&A, &C, 1); Edge CA(&C, &A, 1);
    Edge BC(&B, &C, 2); Edge CB(&C, &B, 2);
    Edge BD(&B, &D, 1); Edge DB(&D, &B, 1);
    Edge CD(&C, &D, 2); Edge DC(&D, &C, 2);
    Edge CE(&C, &E, 3); Edge EC(&E, &C, 3);
    Edge DE(&D, &E, 3); Edge ED(&E, &D, 3);
    Edge DF(&D, &F, 4); Edge FD(&F, &D, 4);
    Edge EF(&E, &F, 1); Edge FE(&F, &E, 1);
    G53.add_vertex(&A); G53.add_vertex(&B); G53.add_vertex(&C); G53.add_vertex(&D); G53.add_vertex(&E); G53.add_vertex(&F);
    G53.add_edge(&AB); G53.add_edge(&BA);
    G53.add_edge(&AC); G53.add_edge(&CA);
    G53.add_edge(&BC); G53.add_edge(&CB);
    G53.add_edge(&BD); G53.add_edge(&DB);
    G53.add_edge(&CD); G53.add_edge(&DC);
    G53.add_edge(&CE); G53.add_edge(&EC);
    G53.add_edge(&DE); G53.add_edge(&ED);
    G53.add_edge(&DF); G53.add_edge(&FD);
    G53.add_edge(&EF); G53.add_edge(&FE);



    std::cout << "prim_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_prim(G53);

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void huffman_test() {

    std::cout << "huffman_test" << std::endl;

    clock_t start, end;
    start = clock();

    vector<char> chs;
    chs.push_back('A'); chs.push_back('B'); chs.push_back('C'); chs.push_back('D');
    unordered_map<char, int> freqs;
    freqs['A'] = 70; freqs['B'] = 3; freqs['C'] = 20; freqs['D'] = 37;

    unordered_map<char, string> code_map = huffman(chs, freqs);
    for (char ch : chs) {
        cout << ch << ": " << code_map[ch] << endl;
    }

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void greedy_activity_selector_test() {

    std::cout << "greedy_activity_selector_test" << std::endl;

    clock_t start, end;
    start = clock();

    vector<vector<int>> sf_time = { {1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{8,11},{8,12},{2,14},{12,16} };
    vector<vector<int>> arrangement = greedy_activity_selector(sf_time);
    for (vector<int> v : arrangement) {
        cout <<  "(" << v[0] << ", " << v[1] << ")" << endl;
    }


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}