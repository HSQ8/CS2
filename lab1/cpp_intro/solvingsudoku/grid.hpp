#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class grid{
private:

    // let x be row, and y be col
    // player interface will be 1 delinieated array, while internal
    // interface will be zero delinated array
    int row = 9, col = 9;
    // the grid representation of the cell
	int gamegrid[9][9];
    // the reference grid that represents the beginnign state, as to 
    // safeguard aginst modifying the original game
	int referenceGrid[9][9];
    // option to output debug statements
    bool mdebug = false;



public:
    grid();
    ~grid();
/**
 * @brief loads board from file
 *
 * this method populates a member variable which representat a
 * esudoku board with a file read in
 * 
 * @param filename a string that specifies the name of the gameboard file to load
 * @return returns nothing
 */
	void loadBoard(string filename);
/**
 * @brief checks if game is finished
 *
 * this method iterates through all cells and check if they are filled
 * if they are filled it  means that the game is solved
 * 
 * @param 
 * @return bool condition stating whether the game has been solved or not
 */
	bool isComplete() const;
/**
 * @brief checks if an attempted move is valid
 * 
 * checks the value val that the user attempts to place
 * at a certain lcoation is valid according to the rules of 
 * sudoku
 * 
 * @param x row coordinate of desired cell
 * @param y col coordinate of desired cell
 * @param val desired value
 * @return bool which states whether the move is valid or not
 */
	bool checkValid(int x, int y, int val) const;
/**
 * @brief attempts to insert val at x,y
 *
 * will attempt to insert the val into the location of the cell 
 * specified by coordinates x, y. Calls checkvalid before inserting
 * if move invalid, will print error message and not insert
 * 
 * @param x row coordinate of desired cell
 * @param y col coordinate of desired cell
 * @param val desired value
 * @return nothing
 */

	void writeNum(int x, int y, int val);
/**
 * @brief undo a move
 *
 * attempts to remove the value at the specified x,y value
 * if the value at the coordinate cell is not part
 * of the game predefined values, then it will be set to empty
 * if it is not already empty 
 *
 * @param x row coordinate of desired cell
 * @param y col coordinate of desired cell
 *
 * @return nothing
 */

	void undoNum(int x, int y);
/**
 * @brief prints the board in an artistic fashion
 *
 * 
 * @param nothign
 * @return nothing
 */

    void display() const;
/**
 * @brief prints the board in an non artisic fashion
 *
 * mostly for debuggin purposes of the actual display function
 * 
 * @param nothign
 * @return nothing
 */
    void simpledisplay() const;
/**
 * @brief returns the number value at the desired x,y location
 * 
 * @param x row coordinate of desired cell
 * @param y col coordinate of desired cell
 * @return int value of the desired cell
 */

    int getNum(int x, int y) const;
/**
 * @brief finds an empty cell from the top left corner
 *
 * goes through the sudoku baord one by one until it finds the first
 * location of the empty cell from the top left
 * 
 * @param nothing
 * @return a pair of ints that describes the location of the empty cel
 */

    std::pair<int, int> getCoordEmptyCell(); 
};