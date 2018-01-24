/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.hpp if you write a helper function!
 */

// swapnum is a function which takes a vector reference, and two list locations
// and swaps the values of the vector at that location
// input list = the list to swap
// input indexA = the first index to swap
// input indexB = the second index to swap
// return nothing
void swapnum(std::vector<int> &list, int indexA, int indexB){
    int temp = list.at(indexA);
    list.at(indexA) = list.at(indexB);
    list.at(indexB) = temp;
}

/**
 * bubble sort traverses down the array and compares each
 * neighboring set of elements and makes sure that they are
 * in order, if not, then it performs a swap on the two elements
 * and moves on to the next pair for comparison
 *for( beginning, end, i)
 * for (beginning, end- 1, i++){
 * compare(i, i+1)
 * if list[i] > list[i+1];
 * swap(list[i],list[i+1]);
 * }
 */

//swapnum

std::vector<int> bubbleSort(std::vector<int> &list)
{
    int maxplace = list.size() - 1;
    while(maxplace > 1){
        for(int i = 0; i < maxplace; ++i){
            if (list[i] > list[i + 1]){
                swapnum(list, i, i + 1);
            }
        }
        maxplace--;
    }
    return list;
}

/**
 * pivotNum is a pivot function that selects a pivot
 * then uses that pivot to organize all points greater than it above it
 * and all points lower than it below it.
 * this uses two indicies to keep track of the location of the low and high swaps
 * and then swaps the pivot value into the appropriate place
 */

int pivotNum(std::vector<int>& v, int low, int high){
    int i = low - 1;
    int pivot = high;
    for(int j = low; j < high; ++j){
        if (v.at(j) < v.at(pivot)){
            i++;
            swapnum(v,i,j);
        }
    }
    swapnum(v, i + 1, high);
    return i+1;
}
/* quick sort function
this function takes in a vector of ints and sorts then by 
recursively partitioning the function into halves by a pivot value
where one half is all lower than the pivot and the other half is all higher 
than the pivot. then it recursively sorts each half of the function until
the base case of a list of length 1 is reached, in at which point the function will be sorted.
the function then merges the two sorted halves back together and return a new list of the same 
values sorted

@param list - the list to be sorted
/*/

std::vector<int> quickSort(std::vector<int> &list)
{
    std::vector<int> newlist = list;
    if (list.size() > 1){
        std::vector<int> leftvec;
        std::vector<int> rightvec;

        std::size_t pivot = list.size() - 1;
        // for debugging purposes
        //std::cout << pivot << list.size() << std::endl;
        int pivotValue = list.at(pivot);
        
        for (std::size_t i = 0; i < list.size(); ++i){
            if(i != pivot){
                if(list.at(i) > pivotValue){
                    rightvec.push_back(list.at(i));
                }else{
                    leftvec.push_back(list.at(i));
                }

            }
        }

        leftvec = quickSort(leftvec);
        rightvec = quickSort(rightvec);
        newlist.clear();
        newlist.insert(newlist.end(), leftvec.begin(), leftvec.end());
        newlist.push_back(pivotValue);
        newlist.insert(newlist.end(), rightvec.begin(), rightvec.end());

    }
    return newlist;
}


/*
the merge sort function recursively splits the list to be sorted into smaller halves
each to be sorted by merge sort and then merged together in increaseing order with 
the helper function merge.
*/
std::vector<int> mergeSort(std::vector<int> &list)
{
    if(list.size() > 1){
        int divide = list.size() / 2;
        std::vector<int> v(list.begin(), list.begin() + divide),
        v2(list.begin() + divide, list.end());
        auto left = mergeSort(v);
        auto right = mergeSort(v2);
        list = merge(left, right);
    }
    return list;
}

/**
 * merge helper function of merge sort
 * this function takes in a left half of a sorted vector and the right half of a sorted vector
 * and merges them in increasing order. first it creates a new list length that would be able to hold 
 * everything, then it compares the beginning elments of the two vectors and adds the smallest one to the 
 * new list. When one list gets used up, the function then attaches the other list to the end of the new list,
 * effectively merging the two together in increasing order.
 */
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    std::vector<int> newarr = std::vector<int>(left.size() + right.size());
    int i = 0, j = 0, leftend = left.size(), rightend = right.size();
    int k = 0;
    while (i < leftend && j < rightend){
        if(left.at(i) < right.at(j)){
            newarr.at(k) = left.at(i);
            ++i;
        }else{
            newarr.at(k) = right.at(j);
            ++j;
        }
        k++;
    }
    while(i < leftend){
        newarr.at(k) = left.at(i);
        ++i;
        ++k;
    }
    while(j < rightend){
        newarr.at(k) = right.at(j);
        ++j;
        ++k;
    }
    return newarr;
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
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    if (left < right){
        int pivot = pivotNum(list, left,right);
        quicksort_inplace(list,pivot + 1, right);
        quicksort_inplace(list,left, pivot - 1);
    }
}
