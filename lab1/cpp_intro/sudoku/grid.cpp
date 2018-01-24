# include "grid.hpp"
# include <string>
# include <cctype>
# include <utility>

void grid::loadBoard(string filename){
    //takes in a filename and populates the private grid member
    // with the number configuration from the file. returns nothing, 
    // it instead modifies a member variable
    // opens a file stream
    ifstream inFile;
    inFile.open(filename);
    if(!inFile){
        std::cout << "File Reading Error" << std::endl;
        exit(1);
    }
    std::string x;
    int localrow = 0;
    //populates the grid
    while(std::getline(inFile, x)){

        for(int i = 0; i < this->col; ++i){

            if(isspace(x.at(i))){
                this->gamegrid[localrow][i] = 0;

            }else {
                this->gamegrid[localrow][i] = x[i] - '0';

            }

        }

        ++localrow;
    }
    // constructs a duplcate board to safeguard
    // against modifying the original numbers on the game
    for(int i = 0; i < this->row; ++i){
        for(int j = 0; j < this->col; ++j){
            this->referenceGrid[i][j] = this->gamegrid[i][j];
        }
    }
    

}
bool grid::isComplete() const{
    // takes nothing and returns a boolean on the complete
    // state of the game
    // iterates through all grid cells
    // to determine whether the board has been 
    // populated in its entirety, 
    // if yes, then the game has been solved.
    for (int i = 0; i < this->row; ++i){
        for (int j = 0; j < this->col; ++j){
            if (this->gamegrid[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}
bool grid::checkValid(int x, int y, int val) const{
    int bigcellsize = 3;
    //takes an x y (row, col) coordinate and a value val (all of which are )
    // ints, and checks whether the val can be inserted at x,y into the
    // game grid based on sudoku rules
    // returns true / false based on whether the move is valid
    // this function checks the given value in the intended cell's validity
    // by checking for the same number in the row and column, as well
    // as i nthe immediate 3x3 grid of the number's residence


    // assume that x and y are betweeen the ranges of [1-9]
    if(!(this->gamegrid[x - 1][y - 1] == 0)){
        return false;
        
    }
    if(this->mdebug)
        cout << "check duplicate pass" << endl;
    for(int i = 0; i < this->row; ++i){
        if (val == this->gamegrid[i][y - 1]){
            return false;
            
        }
    }
    if(this->mdebug)
    cout << "check row pass" << endl;
    for(int i = 0; i < col; ++i){
        if (val == this->gamegrid[x - 1][i]){
            return false;
            
        }
    }
    if(this->mdebug)
    cout << "check col pass" << endl;
    int bigcellrow = (x - 1) / 3;
    int bigcellcol = (y - 1) / 3;
    for (int i = 0; i < bigcellsize; ++i ){
        for(int j = 0; j < bigcellsize; ++j){
            if (val == this->gamegrid[bigcellrow * 3 + i][bigcellcol * 3 + j]){
                return false;
                
            }
        }
    }
    if(this->mdebug)
    cout << "check square pass" << endl;

    return true;
}
void grid::writeNum(int x, int y, int val){
    //takes the x, y (row, col) and value val integers
    // and attempts to insert val at the cell spceified at
    // location x,y
    // returns nothing
    if(checkValid(x, y, val)){
        this->gamegrid[x - 1][y - 1] = val;
    } else{
        //if(this->mdebug)
        cout << "ERROR at writeNum" << endl;
    }
}
void grid::undoNum(int x, int y){
    //takes an x,y coordinate pair (row, col)
    // and attempts to undo the move on taht location
    // returns nothing
    // checks the undo condition where both the inteded undo position
    // must both have a value and must not be a value in the prexisting game board

    if(this->gamegrid[x - 1][y - 1] != 0 && this->referenceGrid[x - 1][y - 1] == 0){
        this->gamegrid[x - 1][y - 1] = 0;
    }else{
        //if(this->mdebug)
        cout << "ERROR, cannot undo" << endl;
    }

}

grid::grid(){
    //constructor initialize the 2d array to zero
    for(int i = 0; i < this->row; ++i){
        for(int j = 0; j < this->col; ++j){
            this->gamegrid[i][j] = 0;
        }
    }
}

void grid::simpledisplay()const{
    // a simplified display function, for debugging purposes
    // takes nothing and returns nothing, it prints the board
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            cout << this->gamegrid[i][j];
        }
        cout << endl;
    }

}

grid::~grid(){}
void grid::display() const{
    // a  display function, for playing game purposes
    // takes nothing and returns nothing, it prints the board
    for(int j = 0; j < 13; ++j){
        for(int i = 0; i < 25; ++i){
            if(j == 0 || j == 4 || j == 8 || j == 12){
                std::cout << "-";
            } else if( i % 2 == 1 ){
                std::cout << ' ';
            } else if(i % 2 == 0 && (i == 0 || i == 24 || i == 8 || i == 16)){
                std::cout << '|';
            } else{
                int m = (i - int(i / 8) * 2 - 1) / 2;
                int l = (j - int(j / 4) - 1);
                if (!this->gamegrid[l][m]){
                    cout << ' ';
                }else{
                    cout << this->gamegrid[l][m];
                }
            }
        }
        std::cout << endl;
    }

}
int grid::getNum(int x, int y) const{
    return this->gamegrid[x - 1][y - 1];
}

std::pair<int, int> grid::getCoordEmptyCell(){
    // gets the first empty cell from the top left corner
    std::pair<int, int> solution;
    for(int i = 0; i < this->row; ++i){
        for(int j = 0; j < this->col; ++j){
            if(this->gamegrid[i][j] == 0){
                solution = std::make_pair(i + 1,j + 1);
                return solution;
            }
        }
    }
    return solution;
}
