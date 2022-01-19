#include <iostream>
#include "./include/matrix.h"
#include "./include/chap0.h"
#include "./include/chap1.h"
#include "./include/chap2.h"

#include "./include/heap.h"



int main()
{   
    int a[15] = { 3,1,4,5,9,2,6,8,7,0 };
    build_maxheap(a, 0, 10);
    cout << maxheap_top(a, 0, 10) << endl;
    cout << maxheap_pop(a, 0, 10) << endl;
    cout << maxheap_pop(a, 0, 9) << endl;
    cout << maxheap_pop(a, 0, 8) << endl;
    maxheap_push(a, 0, 7, 20);
    cout << maxheap_top(a, 0, 8) << endl;
    maxheap_push(a, 0, 8, 25);
    cout << maxheap_top(a, 0, 9) << endl;

    // chap2
    //matrix_multiplication_test();
    //radix_sort_datetime_test();

    while (true) {
        // chap0
        //fib1_test();
        //fib2_test();
        //fib3_test();

        // chap1
        //addition_test();
        //subtraction_test();
        //multiplication_test();
        //division_test();
        //modexp_test();
        //gcd_test();
        //extended_euclid_test();
        //mod_divide_test();
        //primality_test();
        //primality2_test();
        //primality3_test();
        //gen_random_prime_test();
        //naive_AES_test();
        //naive_RSA_test();

        //chap2
        //quicksort_test();
        //mergesort_test();
        //external_mergesort_test();
        //select_test();
        //quantile_test();
        //FFT_test();
        //polynomial_multiplication_test();
        //counting_sort_test();
        //select_from_two_sorted_array_test();
        //major_element_test();

    }


}

