
# include "game.hpp"

void game::getMove(){
    // this function take no argument and returns nothing
    // this function, using getline, parses a line of user input consisting of 
    // both numbers and letters and enforces a certain formatting rule
    // suppose all formatting rules are met, the input is deemed valid, and this function
    // then involks the corresponding operations on the grid object which
    // holds game data

    std::string movecommand;
    std::cout << "<<row,col>>: ";
    std::getline(std::cin, movecommand);
    //
    int x, y, val;

    if(movecommand.length() > 6 && movecommand.at(0) == 'd'){
        x = movecommand.at(2) - '0';
        y = movecommand.at(4) - '0';
        val = movecommand.at(6) - '0';
        if(movecommand.at(1) == ' ' && movecommand.at(3) == ' ' && movecommand.at(5) == ' '){
            this->mygrid.writeNum(x,y,val);
        }else{
            cout << "ERROR, invalid input failed at writeNum check" << endl;
        }

    }else if(movecommand.length() < 7 && movecommand.length() > 2 && movecommand.at(0) == 'u'){
        x = movecommand.at(2) - '0';
        y = movecommand.at(4) - '0';
        //cout << "attempting undoNum" << endl;
        if(movecommand.at(1) == ' ' && movecommand.at(3) == ' '){
            this->mygrid.undoNum(x,y);
        }else{
            cout << "ERROR, invalid input failed at undoNum check" << endl;
        }
    }else if(movecommand.length() < 3 && movecommand.at(0) == 'q'){
        cout << "attempts to quit" << endl;
        exit(0);
    }else{
        cout << "ERROR, invalid move" << endl;
    }
}
void game::run(){
    // run is very simple
    // it takes no arguments are returns nothing
    // run asks the user for a sudoku game to load and 
    // allows the user to continuously enter numbers until
    // the game is solved or until the user
    // decides to quit
    while(!this->mygrid.isComplete()){
        getMove();
        this->mygrid.display();
        
    }
    cout << "SOLVED" << endl;
}
game::game(){
    this->mygrid = grid();
    string filename;
    cout << "input file name: ";
    cin>> filename;
    this->mygrid.loadBoard(filename);
    this->mygrid.display();
    cin.ignore();
}
game::~game(){
}
bool game::solve(){
    // solve function
    // takes in nothing and returns whether it was solved or not
    // recursive backtracking by testing every value at every cell
    // using depth first search to go as far as possible with each 
    // set of parameters before it is forced to back track to last known 
    // good cell

    // uses datastructure std::pair to pass coordinates around
    if(mygrid.isComplete()){
        mygrid.display();
        return true;
    }
        std::pair<int, int> location = mygrid.getCoordEmptyCell();
        for(int i = 1; i < 10; ++i){
            if (mygrid.checkValid(location.first, location.second, i)){
                mygrid.writeNum(location.first, location.second, i);
                if(this->mdebug)
                mygrid.display();
                if(solve()){ //recursive depth first search
                    return true;
                } else{ // backtrack
                    mygrid.undoNum(location.first, location.second);
                }
            }
        }
        return false;   
}