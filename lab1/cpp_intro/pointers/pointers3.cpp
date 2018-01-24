/**
 * @file pointers3.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 3: "Entangled" pointers
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief Set two pointers to the same memory and free them.
 */
int main(int argc, char *argv[])
{
    int *a, *b;

    // Allocate an array of 10 ints.
    a = (int *) malloc(10 * sizeof(int));

    // Now `b` points to the same array of ints.
    b = a;

    
        free(a);
        a = NULL;
        b = NULL;


        free(b);
    //  the error is that we free a, which points to the same
    //  address as b, when we attempt to free b, we have already
    //  freed the memory location that we want to free when we freed
    //  a, thus I have fixed it by settings pointers to null

    return 0;
}
