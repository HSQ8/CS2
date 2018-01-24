/**
 * @file testFileIO.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input.
 */

#include "fileio.hpp"

/**
 * @brief Read the file input and print out its contents
 *
 * Assumes that the file contains one integer per line.
 */
int main(int argc, char const *argv[])
{
    std::vector<int> v;

    for (int i = 1; i < argc; ++i)
    {
         readFile(argv[i], v);
         print_vector(v);
         v.clear();
    }
    std::cout << std::endl;

    return 0;
}
