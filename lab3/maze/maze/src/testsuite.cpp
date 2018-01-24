/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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

#include <cstdio>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"
#include <iostream>


void display(Coordinate c){
    std::cout << "cordinate: x:" << c.x << " y:" << c.y << std::endl;
}

int main()
{
    Coordinate c;
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();
    std::cout << "testing stack push 1,1 \n";
    stack->push(Coordinate(1,1));
    std::cout << "testing stack push 2,2\n";
    stack->push(Coordinate(2,2));
    std::cout << "testing stack push 3,3\n";
    stack->push(Coordinate(3,3));
    std::cout << "testing stack push 4,4\n";
    stack->push(Coordinate(4,4));
    std::cout << "testing stack push 5,5\n";
    stack->push(Coordinate(5,5));
    while(!stack->is_empty()){
        std::cout << "testing stack peek ==";
        display (stack->peek());

        std::cout << "testing stack pop ==";

        display (stack->pop());
    }

    std::cout << "testing queue enque 1,1\n";
    queue->enqueue(Coordinate   (1,1));
    std::cout << "testing queue enque 2,2\n";
    queue->enqueue(Coordinate   (2,2));
    std::cout << "testing queue enque 3,3\n";
    queue->enqueue(Coordinate   (3,3));
    std::cout << "testing queue enque 4,4\n";
    queue->enqueue(Coordinate   (4,4));
    std::cout << "testing queue enque 5,5\n";
    queue->enqueue(Coordinate   (5,5));
    while(!queue->is_empty()){
        std::cout << "testing queue peek ==";
        display (queue->peek());
        std::cout << "testing queue deque ==";
        display (queue->dequeue());
    }

    /* TODO: Test all the things! */

    delete queue;
    delete stack;

    return 0;
}
