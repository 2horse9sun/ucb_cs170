#include <iostream>
#include "./include/chap0.h"
#include "./include/chap1.h"
#include "./include/chap2.h"
#include "./include/matrix.h"



int main()
{   
    Matrix<int> X(2, 3);
    X(1, 1) = 1; X(1, 2) = 2; X(1, 3) = 3; X(2, 1) = 4; X(2, 2) = 5; X(2, 3) = 6;
    Matrix<int> Y(3, 2);
    Y(1, 1) = 1; Y(1, 2) = 0; Y(2, 1) = 0; Y(2, 2) = 1; Y(3, 1) = 1; Y(3, 2) = 0;
    cout << X * Y;

    //Matrix<int> X(2, 2);
    //X(1, 1) = 1; X(1, 2) = 2; X(2, 1) = 4; X(2, 2) = 5; 
    //Matrix<int> Y(2, 2);
    //Y(1, 1) = 1; Y(1, 2) = 0; Y(2, 1) = 0; Y(2, 2) = 1; 
    //cout << X * Y;

    //while (true) {

    //    //fib1_test();
    //    //fib2_test();
    //    //fib3_test();

    //    //addition_test();
    //    //subtraction_test();
    //    //multiplication_test();
    //    //division_test();
    //    //modexp_test();
    //    //euclid_test();
    //    //extended_euclid_test();
    //    //mod_divide_test();
    //    //primality_test();
    //    //primality2_test();
    //    //primality3_test();
    //    //gen_random_prime_test();
    //    //naive_AES_test();
    //    //naive_RSA_test();

    //    //mergesort_test();
    //    //quicksort_test();
    //    
    //    select_test();

    //}
}

