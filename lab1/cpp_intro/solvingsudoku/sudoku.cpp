#include "game.hpp"
int main(){
    // main function, instatiates a game object and runs the game
    // the game object can either run or solve, where
    // in run, the game provides an interface for a human player
    // and in the case of solve, the program solves itself
    game mygame = game();
    mygame.solve();
    return 0;
}