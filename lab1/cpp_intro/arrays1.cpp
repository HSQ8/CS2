/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

using namespace std;

//
// TODO: put user functions here
//

int max(int _arr[], int size){
    int max = _arr[size - 1];
    for (std::size_t i = 0; i < size; ++i){
        if (_arr[i] > max){
            max = _arr[i];
        }
    }
    return max;
}
double mean(int _arr[], int size){
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i){
        sum += _arr[i];
    }
    return ((double)sum) / size;
}
void ascend(int _arr[], int size){
    for (std::size_t i = 0; i < size; ++i){
        _arr[i] = i;
    }
}
void printarray(int _arr[], int size){
    for(std::size_t i = 0; i < size; ++i){
        cout << _arr[i] << ",";
    }
}




/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int test_values[TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    //
    // TODO: do your stuff here with the array `test_values`
    // of dynamic size `real_size`
    //

    cout << "max" << max(test_values, real_size) << endl;
    cout << "mean" << mean(test_values, real_size) << endl;
    printarray(test_values, real_size);
    ascend(test_values, real_size);
    printarray(test_values, real_size);
}
