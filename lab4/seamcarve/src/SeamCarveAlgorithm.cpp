/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"
#include<iostream>                                                                                                                                                                                                                                                                                                                                                                                                    

#define min(x, y)           ((x) < (y) ? (x) : (y))



/**
 * Getseam traverses the cost matrix to find the least costing path from the bottom
 * recursively calls itself to traverse through the costmatrix vertically and populates the seam until
 * we run out of levels to compute
 * @param costmatrix cost matrix is the matrix of costs computed in the previous stem
 * @param w          width of the cost matrix
 * @param h          height of the cost matrix
 * @param seam       the seam, a list of width locations through the cost matrix
 * @param level      the current level at which we evaluate for the position of the next seam
 * @param col        the next column that we want to set the seat to go to
 */
void getSeam(unsigned int **costmatrix, int w, int h, unsigned int* seam, int level, int col){
    if(level == 0){
        seam[h - 1 - level] = col;
    }else{
        seam[h - 1 - level] = col;
        if(col != 0 && col != w - 1){
            int curcolindex = -1;
            unsigned int curcolval = costmatrix[col + curcolindex][level - 1];
            if(costmatrix[col][level - 1] < curcolval){
                curcolindex = 0;
                curcolval = costmatrix[col][level - 1];
            }
            if(costmatrix[col + 1][level - 1] < curcolval){
                curcolindex = 1;
            }
            getSeam(costmatrix, w,h,seam,level - 1, col + curcolindex);
        }else if(col == 0){
            int curcolindex = 0;
            unsigned int curcolval = costmatrix[col + curcolindex][level - 1];
            if(costmatrix[col + 1][level - 1] < curcolval){
                curcolindex = 1;
            }
            getSeam(costmatrix, w,h,seam,level - 1, col + curcolindex);

        }else if(col == (w-1)){
            int curcolindex = -1;
            unsigned int curcolval = costmatrix[col + curcolindex][level - 1];
            if(costmatrix[col][level - 1] < curcolval){
                curcolindex = 0;
            }
            getSeam(costmatrix, w,h,seam,level - 1, col + curcolindex);
        }         
    }

}


/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    /* TODO: Write this function! */
    //computes costmatrix

    unsigned int **costmatrix = new unsigned int*[w];
    for(int i=0; i< w; ++i){
        costmatrix[i] = new unsigned int[h];
    }

    for(int i = 0; i < w; ++i){
        costmatrix[i][0] = smap[i][0];
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    for(int i = 1; i < h; ++i){
        costmatrix[0][i] = smap[0][i] + min(costmatrix[0][i - 1], costmatrix[1][i-1]);
        for(int j = 1; j < w - 1; ++j){
            costmatrix[j][i] = smap[j][i] + min(min(costmatrix[j][i - 1], costmatrix[j - 1][i - 1]), costmatrix[j + 1][i-1]);
        }
        costmatrix[w - 1][i] = smap[w-1][i] + min(costmatrix[w - 1][i - 1] ,costmatrix[w - 2][i-1]);
    }
    //computes seam
    unsigned int *seam = new unsigned int[h];
    unsigned int lowestval = costmatrix[0][h-1];
    unsigned int lowest = 0;
    for (int i = 0; i < w; ++i){
        if (costmatrix[i][h-1] < lowestval){
            lowest = i;
        }
    }
    std::cout<<lowest<<std::endl;
    getSeam(costmatrix, w, h,seam,h-1,lowest);

    for(int i = 0; i < w; ++i){
        delete[] costmatrix[i];
    }
    delete[] costmatrix;

    return seam;
} 

