# include "grid.hpp"
#include <utility>

using namespace std;
class game{
private:
    grid mygrid;
    bool mdebug = false;
public:
/**
 * @brief provides an method that parses user input
 *
 * this method is run to allow the user to
 * enter commands such as d 1 1 2(place value of 2 at 1, 1), 
 * and u 2 2 (undo at 2, 2 ).
 * 
 * @param takes nothing
 * @return returns nothing
 */
    void getMove();
/**
 * @brief provides an interface for the user to solve a sudoku puzzle
 *
 * this method runs the interface of the sudoku game and calls the 
 * getmove function to iteratively display and allow the use to
 * enter commands
 * 
 * @param takes nothing
 * @return returns nothing
 */
    void run();
/**
 * @brief solves the sudoku puzzle constructed in the constructor
 * 
 * this function given an exsiting board in the member varialbe solves
 * it by using recursive backtracking. It uses depths first search to 
 * search for possible values in each cell and tries to go as far as possible
 * without getting in invalid cell, at which point will will back track to the
 * last known good cell. Uses the datastructure std::pair<int,int> inorder to 
 * pass the coodinates of the cells around
 * 
 * @param takes nothing
 * @return returns nothing
 */
    bool solve();

/**
 *@brief a simple constructor that allows user to load a sudoku game file
 */
    game();
/**
 * @brief destructor
 */
    ~game();
};