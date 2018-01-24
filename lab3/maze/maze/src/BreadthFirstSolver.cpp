/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "BreadthFirstSolver.hpp"
#include<algorithm>
/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{ 
   for(int i = 0; i < WIDTH; ++i){
        for(int j = 0; j < HEIGHT; ++j){
            visited[i][j].visited = false;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
BreadthFirstSolver::~BreadthFirstSolver()
{
    deinit();
}

/**
 * @brief Deinitializes the solver (student-implemented).
 * deletes the only dynamically allocated variable
 */
void BreadthFirstSolver::deinit()
{
    delete this->queue;
}

/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
this->queue->enqueue(Coordinate(MAZE_START_X, MAZE_START_Y));
    this->visited[MAZE_START_X][MAZE_START_Y].visited = true;

    while(!this->queue->is_empty()){

    Coordinate c = this->queue->peek();
    this->visited[c.x][c.y].visited = true;
    if(c.x == MAZE_END_X && c.y == MAZE_END_Y){
        return;
    }
    int res = maze->get_possible_moves(c.x, c.y);

    if (res & E && !this->visited[c.x + 1][c.y].visited) {
        this->queue->enqueue(Coordinate(c.x + 1, c.y));
        this->visited[c.x+1][c.y].from = c;
    }
    if (res & S && !this->visited[c.x][c.y + 1].visited) {
    this->queue->enqueue(Coordinate(c.x, c.y + 1));
    this->visited[c.x][c.y + 1].from = c;
    }
    if (res & N && !this->visited[c.x][c.y - 1].visited) {
    this->queue->enqueue(Coordinate(c.x, c.y - 1));
    this->visited[c.x][c.y - 1].from = c;
    }
    if (res & W && !this->visited[c.x - 1][c.y].visited) {
    this->queue->enqueue(Coordinate(c.x - 1, c.y));
    this->visited[c.x - 1][c.y].from = c;
    }
    this->queue->dequeue();
}
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 * this works by backtracking the visited.from element in the 
 * visited array until it reaches maze start
 */
vector<Coordinate> BreadthFirstSolver::get_path()
{
    vector<Coordinate> list;
    Coordinate c = this->queue->peek();
    list.push_back(c);
    while(c.x != MAZE_START_X || c.y != MAZE_START_Y){
        c = this->visited[c.x][c.y].from;
        list.push_back(c);
    }
    return list;
}

