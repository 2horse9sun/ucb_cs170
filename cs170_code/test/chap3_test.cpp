#include <iostream>
#include <time.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../include/chap3.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"


void undirected_graph_test() {

    // Fig 3.2
    Graph G32 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Vertex G("G"); Vertex H("H"); Vertex I("I"); Vertex J("J"); Vertex K("K"); Vertex L("L");
    Edge AB(&A, &B); Edge BA(&B, &A);
    Edge AC(&A, &C); Edge CA(&C, &A);
    Edge AD(&A, &D); Edge DA(&D, &A);
    Edge BE(&B, &E); Edge EB(&E, &B);
    Edge BF(&B, &F); Edge FB(&F, &B);
    Edge CF(&C, &F); Edge FC(&F, &C);
    Edge DG(&D, &G); Edge GD(&G, &D);
    Edge DH(&D, &H); Edge HD(&H, &D);
    Edge EI(&E, &I); Edge IE(&I, &E);
    Edge EJ(&E, &J); Edge JE(&J, &E);
    Edge GH(&G, &H); Edge HG(&H, &G);
    Edge IJ(&I, &J); Edge JI(&J, &I);
    Edge KL(&K, &L); Edge LK(&L, &K);
    G32.add_vertex(&A); G32.add_vertex(&B); G32.add_vertex(&C); G32.add_vertex(&D); G32.add_vertex(&E); G32.add_vertex(&F);
    G32.add_vertex(&G); G32.add_vertex(&H); G32.add_vertex(&I); G32.add_vertex(&J); G32.add_vertex(&K); G32.add_vertex(&L);
    G32.add_edge(&AB); G32.add_edge(&BA);
    G32.add_edge(&AC); G32.add_edge(&CA);
    G32.add_edge(&AD); G32.add_edge(&DA);
    G32.add_edge(&BE); G32.add_edge(&EB);
    G32.add_edge(&BF); G32.add_edge(&FB);
    G32.add_edge(&CF); G32.add_edge(&FC);
    G32.add_edge(&DG); G32.add_edge(&GD);
    G32.add_edge(&DH); G32.add_edge(&HD);
    G32.add_edge(&EI); G32.add_edge(&IE);
    G32.add_edge(&EJ); G32.add_edge(&JE);
    G32.add_edge(&GH); G32.add_edge(&HG);
    G32.add_edge(&IJ); G32.add_edge(&JI);
    G32.add_edge(&KL); G32.add_edge(&LK);



    std::cout << "undirected_graph_test" << std::endl;

    clock_t start, end;
    start = clock();

    std::cout << "Vertices: ";
    G32.print_vertices();
    std::cout << endl;
    std::cout << "Edges: ";
    G32.print_edges();
    std::cout << endl;
    std::cout << "Neighbours of B: ";
    G32.print_neighbours(&B);
    std::cout << endl;

    G32.remove_vertex(&A);
    G32.remove_edge(&EI);
    G32.remove_edge(&IE);
    G32.remove_edge(&EJ);
    G32.remove_edge(&JE);
    std::cout << "Remaining Vertices: ";
    G32.print_vertices();
    std::cout << endl;
    std::cout << "Remaining Edges: ";
    G32.print_edges();
    std::cout << endl;
    std::cout << "Neighbours of B: ";
    G32.print_neighbours(&B);
    std::cout << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void dfs_test() {
    // Fig 3.2
    Graph G32 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Vertex G("G"); Vertex H("H"); Vertex I("I"); Vertex J("J"); Vertex K("K"); Vertex L("L");
    Edge AB(&A, &B); Edge BA(&B, &A);
    Edge AC(&A, &C); Edge CA(&C, &A);
    Edge AD(&A, &D); Edge DA(&D, &A);
    Edge BE(&B, &E); Edge EB(&E, &B);
    Edge BF(&B, &F); Edge FB(&F, &B);
    Edge CF(&C, &F); Edge FC(&F, &C);
    Edge DG(&D, &G); Edge GD(&G, &D);
    Edge DH(&D, &H); Edge HD(&H, &D);
    Edge EI(&E, &I); Edge IE(&I, &E);
    Edge EJ(&E, &J); Edge JE(&J, &E);
    Edge GH(&G, &H); Edge HG(&H, &G);
    Edge IJ(&I, &J); Edge JI(&J, &I);
    Edge KL(&K, &L); Edge LK(&L, &K);
    G32.add_vertex(&A); G32.add_vertex(&B); G32.add_vertex(&C); G32.add_vertex(&D); G32.add_vertex(&E); G32.add_vertex(&F);
    G32.add_vertex(&G); G32.add_vertex(&H); G32.add_vertex(&I); G32.add_vertex(&J); G32.add_vertex(&K); G32.add_vertex(&L);
    G32.add_edge(&AB); G32.add_edge(&BA);
    G32.add_edge(&AC); G32.add_edge(&CA);
    G32.add_edge(&AD); G32.add_edge(&DA);
    G32.add_edge(&BE); G32.add_edge(&EB);
    G32.add_edge(&BF); G32.add_edge(&FB);
    G32.add_edge(&CF); G32.add_edge(&FC);
    G32.add_edge(&DG); G32.add_edge(&GD);
    G32.add_edge(&DH); G32.add_edge(&HD);
    G32.add_edge(&EI); G32.add_edge(&IE);
    G32.add_edge(&EJ); G32.add_edge(&JE);
    G32.add_edge(&GH); G32.add_edge(&HG);
    G32.add_edge(&IJ); G32.add_edge(&JI);
    G32.add_edge(&KL); G32.add_edge(&LK);



    std::cout << "dfs_test" << std::endl;

    clock_t start, end;
    start = clock();

    dfs(G32);

    std::cout << std::endl;
    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void undirected_cc_test() {
    // Fig 3.2
    Graph G32 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Vertex G("G"); Vertex H("H"); Vertex I("I"); Vertex J("J"); Vertex K("K"); Vertex L("L");
    Edge AB(&A, &B); Edge BA(&B, &A);
    Edge AC(&A, &C); Edge CA(&C, &A);
    Edge AD(&A, &D); Edge DA(&D, &A);
    Edge BE(&B, &E); Edge EB(&E, &B);
    Edge BF(&B, &F); Edge FB(&F, &B);
    Edge CF(&C, &F); Edge FC(&F, &C);
    Edge DG(&D, &G); Edge GD(&G, &D);
    Edge DH(&D, &H); Edge HD(&H, &D);
    Edge EI(&E, &I); Edge IE(&I, &E);
    Edge EJ(&E, &J); Edge JE(&J, &E);
    Edge GH(&G, &H); Edge HG(&H, &G);
    Edge IJ(&I, &J); Edge JI(&J, &I);
    Edge KL(&K, &L); Edge LK(&L, &K);
    G32.add_vertex(&A); G32.add_vertex(&B); G32.add_vertex(&C); G32.add_vertex(&D); G32.add_vertex(&E); G32.add_vertex(&F);
    G32.add_vertex(&G); G32.add_vertex(&H); G32.add_vertex(&I); G32.add_vertex(&J); G32.add_vertex(&K); G32.add_vertex(&L);
    G32.add_edge(&AB); G32.add_edge(&BA);
    G32.add_edge(&AC); G32.add_edge(&CA);
    G32.add_edge(&AD); G32.add_edge(&DA);
    G32.add_edge(&BE); G32.add_edge(&EB);
    G32.add_edge(&BF); G32.add_edge(&FB);
    G32.add_edge(&CF); G32.add_edge(&FC);
    G32.add_edge(&DG); G32.add_edge(&GD);
    G32.add_edge(&DH); G32.add_edge(&HD);
    G32.add_edge(&EI); G32.add_edge(&IE);
    G32.add_edge(&EJ); G32.add_edge(&JE);
    G32.add_edge(&GH); G32.add_edge(&HG);
    G32.add_edge(&IJ); G32.add_edge(&JI);
    G32.add_edge(&KL); G32.add_edge(&LK);



    std::cout << "undirected_cc_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_undirected_cc(G32);

    std::cout << std::endl;
    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void dag_topological_sort_test() {
    // Fig 3.8
    Graph G38 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Edge AC(&A, &C); 
    Edge BA(&B, &A);
    Edge BD(&B, &D);
    Edge CE(&C, &E);
    Edge CF(&C, &F);
    Edge DC(&D, &C);
    G38.add_vertex(&A); G38.add_vertex(&B); G38.add_vertex(&C); G38.add_vertex(&D); G38.add_vertex(&E); G38.add_vertex(&F);
    G38.add_edge(&AC); 
    G38.add_edge(&BA);
    G38.add_edge(&BD);
    G38.add_edge(&CE);
    G38.add_edge(&CF);
    G38.add_edge(&DC);

    std::cout << "dag_topological_sort_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_dag_topological_sort(G38);

    std::cout << std::endl;
    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void directed_scc_test() {
    // Fig 3.9
    Graph G39 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); Vertex F("F");
    Vertex G("G"); Vertex H("H"); Vertex I("I"); Vertex J("J"); Vertex K("K"); Vertex L("L");
    Edge AB(&A, &B); 
    Edge BC(&B, &C);
    Edge BD(&B, &D);
    Edge BE(&B, &E);
    Edge CF(&C, &F);
    Edge EB(&E, &B);
    Edge EF(&E, &F);
    Edge EG(&E, &G);
    Edge FC(&F, &C);
    Edge FH(&F, &H);
    Edge GH(&G, &H);
    Edge GJ(&G, &J);
    Edge HK(&H, &K);
    Edge IG(&I, &G);
    Edge JI(&J, &I);
    Edge KL(&K, &L);
    Edge LJ(&L, &J);
    G39.add_vertex(&A); G39.add_vertex(&B); G39.add_vertex(&C); G39.add_vertex(&D); G39.add_vertex(&E); G39.add_vertex(&F);
    G39.add_vertex(&G); G39.add_vertex(&H); G39.add_vertex(&I); G39.add_vertex(&J); G39.add_vertex(&K); G39.add_vertex(&L);
    G39.add_edge(&AB); 
    G39.add_edge(&BC);
    G39.add_edge(&BD);
    G39.add_edge(&BE);
    G39.add_edge(&CF);
    G39.add_edge(&EB);
    G39.add_edge(&EF);
    G39.add_edge(&EG);
    G39.add_edge(&FC);
    G39.add_edge(&FH);
    G39.add_edge(&GH);
    G39.add_edge(&GJ);
    G39.add_edge(&HK);
    G39.add_edge(&IG);
    G39.add_edge(&JI);
    G39.add_edge(&KL);
    G39.add_edge(&LJ);


    std::cout << "directed_scc_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_directed_scc(G39);

    std::cout << std::endl;
    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}