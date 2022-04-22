#include <iostream>
#include <time.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../include/chap4.h"
#include "../include/vertex.h"
#include "../include/edge.h"
#include "../include/graph.h"


void bfs_test() {
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



    std::cout << "bfs_test" << std::endl;

    clock_t start, end;
    start = clock();

    bfs(G32, &A);
    bfs(G32, &K);

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void bellman_ford_test() {
    // Fig 4.14
    Graph G414 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); 
    Vertex E("E"); Vertex F("F"); Vertex G("G"); Vertex S("S"); 
    Edge AE(&A, &E, 2); 
    Edge BA(&B, &A, 1);
    Edge BC(&B, &C, 1);
    Edge CD(&C, &D, 3);
    Edge DE(&D, &E, -1);
    Edge EB(&E, &B, -2);
    Edge FA(&F, &A, -4);
    Edge FE(&F, &E, -1);
    Edge GF(&G, &F, 1);
    Edge SA(&S, &A, 10);
    Edge SG(&S, &G, 8);
    G414.add_vertex(&A); G414.add_vertex(&B); G414.add_vertex(&C); G414.add_vertex(&D);
    G414.add_vertex(&E); G414.add_vertex(&F); G414.add_vertex(&G); G414.add_vertex(&S);
    G414.add_edge(&AE); 
    G414.add_edge(&BA);
    G414.add_edge(&BC);
    G414.add_edge(&CD);
    G414.add_edge(&DE);
    G414.add_edge(&EB);
    G414.add_edge(&FA);
    G414.add_edge(&FE);
    G414.add_edge(&GF);
    G414.add_edge(&SA);
    G414.add_edge(&SG);



    std::cout << "bellman_ford_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_bellman_ford(G414, &S);

    cout << "Add a negative cycle: ";
    CD.update_weight(-2);
    BC.update_weight(-1);
    print_bellman_ford(G414, &S);

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void dag_shortest_path_test() {
    // Fig 4.14 with edge EB removed
    Graph G414 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); 
    Vertex E("E"); Vertex F("F"); Vertex G("G"); Vertex S("S"); 
    Edge AE(&A, &E, 2); 
    Edge BA(&B, &A, 1);
    Edge BC(&B, &C, 1);
    Edge CD(&C, &D, 3);
    Edge DE(&D, &E, -1);
    Edge EB(&E, &B, -2);
    Edge FA(&F, &A, -4);
    Edge FE(&F, &E, -1);
    Edge GF(&G, &F, 1);
    Edge SA(&S, &A, 10);
    Edge SG(&S, &G, 8);
    G414.add_vertex(&A); G414.add_vertex(&B); G414.add_vertex(&C); G414.add_vertex(&D);
    G414.add_vertex(&E); G414.add_vertex(&F); G414.add_vertex(&G); G414.add_vertex(&S);
    G414.add_edge(&AE); 
    G414.add_edge(&BA);
    G414.add_edge(&BC);
    G414.add_edge(&CD);
    G414.add_edge(&DE);
    G414.add_edge(&EB);
    G414.add_edge(&FA);
    G414.add_edge(&FE);
    G414.add_edge(&GF);
    G414.add_edge(&SA);
    G414.add_edge(&SG);



    std::cout << "dag_shortest_path_test" << std::endl;

    clock_t start, end;
    start = clock();

    G414.remove_edge(&EB);
    print_dag_shortest_path(G414, &S);


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void dijkstra_test() {
    // Fig 4.9
    Graph G49 = Graph();
    Vertex A("A"); Vertex B("B"); Vertex C("C"); Vertex D("D"); Vertex E("E"); 
    Edge AB(&A, &B, 4);
    Edge AC(&A, &C, 2);
    Edge BC(&B, &C, 3);
    Edge BD(&B, &D, 2);
    Edge BE(&B, &E, 3);
    Edge CB(&C, &B, 1);
    Edge CD(&C, &D, 4);
    Edge CE(&C, &E, 5);
    Edge ED(&E, &D, 1);
    G49.add_vertex(&A); G49.add_vertex(&B); G49.add_vertex(&C); G49.add_vertex(&D); G49.add_vertex(&E);
    G49.add_edge(&AB);
    G49.add_edge(&AC);
    G49.add_edge(&BC);
    G49.add_edge(&BD);
    G49.add_edge(&BE);
    G49.add_edge(&CB);
    G49.add_edge(&CD);
    G49.add_edge(&CE);
    G49.add_edge(&ED);
    



    std::cout << "dijkstra_test" << std::endl;

    clock_t start, end;
    start = clock();

    print_dijkstra(G49, &A);


    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}