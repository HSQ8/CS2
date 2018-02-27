/**
 * @file EulerIntegrator.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions that carry out numerical integration.
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

#include "EulerIntegrator.hpp"

float EulerIntegrator::get_x_acceleration(double *x, double *y){
    return (*x)*(-1.0) / std::pow(((*x)*(*x) + (*y)*(*y)), 3.0/2.0);
}
float EulerIntegrator::get_y_acceleration(double *x, double *y){
    return (*y)*(-1.0) / std::pow(((*x)*(*x) + (*y)*(*y)), 3.0/2.0);
}


/**
 * @brief Solve a differential equation with the forward Euler method.
 *
 * @param[in,out] x The x-coordinate.
 *
 * @param[in,out] y The y-coordinate.
 *
 * @param[in,out] vx The velocity in the x direction.
 *
 * @param[in,out] vy The velocity in the y direction.
 *
 * @param[in] h A small timestep.
 */
void EulerIntegrator::forward_euler(double *x, double *y, double *vx,
    double *vy, double h)
{
    double curx = *x;
    double cury = *y;
    *x += h * (*vx);
    *y += h * (*vy);
    *vx += h* get_x_acceleration(&curx, &cury);
    *vy += h* get_y_acceleration(&curx, &cury);
}


/**
 * @brief Solve a differential equation with the backward Euler method.
 *
 * @param[in,out] x The x-coordinate.
 *
 * @param[in,out] y The y-coordinate.
 *
 * @param[in,out] vx The velocity in the x direction.
 *
 * @param[in,out] vy The velocity in the y direction.
 *
 * @param[in] h A small timestep.
 */
void EulerIntegrator::backward_euler(double *x, double *y, double *vx,
    double *vy, double h)
{

    *x = ((*x) + h *(*vx))/(1.0+h*h);
    *y = ((*y) + h *(*vy))/(1.0+h*h);
    *vx = *vx + h*(get_x_acceleration(x,y));
    *vy = *vy + h*(get_y_acceleration(x,y));
}


/**
 * @brief Solve a differential equation with the symplectic Euler method.
 *
 * @param[in,out] x The x-coordinate.
 *
 * @param[in,out] y The y-coordinate.
 *
 * @param[in,out] vx The velocity in the x direction.
 *
 * @param[in,out] vy The velocity in the y direction.
 *
 * @param[in] h A small timestep.
 */
void EulerIntegrator::symplectic_euler(double *x, double *y, double *vx,
    double *vy, double h)
{
    double curx = *x;
    double cury = *y;
    *vx += h* get_x_acceleration(&curx, &cury);
    *vy += h* get_y_acceleration(&curx, &cury);
    *x += h * (*vx);
    *y += h * (*vy);
}
