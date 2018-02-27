/**
 * @file test_solver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Simple test suite for Solver.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
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

#include "Solver.hpp"
#include <cstdio>

using namespace Solver;

double f1(double x){
    return x*x*x - x + 1.0;
}
double f1prime(double x){
    return 3*x*x - 1.0;
}

double f2(double x){
    return x*x*x*x*x - x*x*x*x + 3*x*x*x - 6.0;
}
double f2prime(double x){
    return 5*x*x*x*x - 4*x*x*x + 9*x*x;
}


int main()
{
    double (*f1ptr)(double);
    double (*f1PrimePtr)(double);
    f1ptr = &f1;
    f1PrimePtr = &f1prime;

    double (*f2ptr)(double);
    double (*f2PrimePtr)(double);
    f2ptr = &f2;
    f2PrimePtr = &f2prime;

    std::cout << "x*x*x - x + 1.0 , root should be  -1.324718" << std::endl;
    std::cout << "bisection method " << bisection(f1ptr,-5.0, 5.0) << std::endl; // should be -1.324718
    std::cout << "newton raphson method " << newton_raphson(f1ptr, f1PrimePtr, 10) << std::endl; // should -1.324718

    std::cout << "x*x*x*x*x - x*x*x*x + 3*x*x*x - 6.0 , root should be  1.2237652" << std::endl;
    std::cout << "bisection method " << bisection(f2ptr,-5.0, 5.0) << std::endl; // should  be 1.2237652
    std::cout << "newton raphson method " << newton_raphson(f2ptr, f2PrimePtr, 10) << std::endl; // should  be 1.2237652
    return 0;
}
