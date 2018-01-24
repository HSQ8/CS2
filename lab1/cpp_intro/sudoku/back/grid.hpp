#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class grid{
private:

    // let x be row, and y be col
    // player interface will be 1 delinieated array, while internal
    // interface will be zero delinated array
    int row = 9, col = 9;
	int gamegrid[9][9];
	int referenceGrid[9][9];



public:
    grid();
    ~grid();

	void loadBoard(string filename);
	bool isComplete() const;
	bool checkValid(int x, int y, int val) const;
	void writeNum(int x, int y, int val);
	void undoNum(int x, int y);
    void display() const;
    void simpledisplay() const;
};