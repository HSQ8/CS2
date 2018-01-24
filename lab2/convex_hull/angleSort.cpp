/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>



// swapnum is a function which takes a vector reference, and two index locations
// and swaps the values of the vector at that location
// input list = the list to swap
// input indexA = the first index to swap
// input indexB = the second index to swap
// return nothing
void swapnum(std::vector<double> &list, int indexA, int indexB);


// swapnum is a function which takes a vector reference, and two index locations
// and swaps the pointer values of the vector at that location
// input list = the list to swap
// input indexA = the first index to swap
// input indexB = the second index to swap
// return nothing
void swapPointer(vector<Tuple*> &points, int a1, int a2);

/**
 * pivotNum is a pivot function that selects a pivot
 * then uses that pivot to organize all points greater than it above it
 * and all points lower than it below it.
 * this uses two indicies to keep track of the location of the low and high swaps
 * and then swaps the pivot value into the appropriate place
 */
int pivotNum(std::vector<double>& v, int low, int high, vector<Tuple*> &points){
    int i = low - 1;
    int pivot = high;
    for(int j = low; j < high; ++j){
        if (v.at(j) < v.at(pivot)){
            i++;
            swapnum(v,i,j);
            swapPointer(points, i, j);
        }
    }
    swapnum(v, i + 1, high);
    swapPointer(points, i + 1, high);
    return i+1;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.

 note - this version has been modified to take in an additional vector of points
 so that the points can be swapped inthe same fashion as the angles.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 */

void quicksort_inplace(std::vector<double> &list, int left, int right, vector<Tuple*> &points)
{
    if (left < right){
        int pivot = pivotNum(list, left,right, points);
        quicksort_inplace(list,pivot + 1, right, points);
        quicksort_inplace(list,left, pivot - 1, points);
    }
}
//documation above
void swapPointer(vector<Tuple*> &points, int a1, int a2){
    Tuple * tempPtr = points.at(a1);
    points.at(a1) = points.at(a2);
    points.at(a2) = tempPtr;
}
//documentation above
void swapnum(std::vector<double> &list, int indexA, int indexB){
    double temp = list.at(indexA);
    list.at(indexA) = list.at(indexB);
    list.at(indexB) = temp;
}

//sort function takes in a vector of angles <double> and a vector 
// of point tuples and sorts them in ascending order. the underlying algorithm uses
// quicksort, but slightly modified to take in an extra argument list and mirror the 
// operations of the list on it.
void sort(vector<Tuple*> &points, vector<double> &angles)
{
    quicksort_inplace(angles, 0, angles.size() - 1, points);
    
}

int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
