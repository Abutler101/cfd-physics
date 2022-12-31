//
// Created by Alexis on 31/12/2022.
//
#include "headers/physics.h"
#include "utils.hpp"

namespace physics{
    void diffuse(BoundaryMode bm, float *grid[], float *previous_grid[], GridInfo sizes, float dampening, float dt, int itters){
    /*
     * Diffuses the given value grid with the logic of flowing from
     * high to low
     */
        //...
    }

    void project(float *v_x[], float *v_y[], float *prev[], float *divisor[], GridInfo sizes, int itters){
    /*
     * Balances velocities such that the fluid remains incompressible &
     * density is neither created nor destroyed by the solver
     */
        //...

    }

    void advect(BoundaryMode bm, float *grid[], float *prev_grid[], float *veloc_x[], float *veloc_y[], GridInfo sizes, float dt){
    /*
     * Distributes the given value grid based on the given velocity grid
     */
        //...
    }

    void enforce_boundaries(BoundaryMode bm, float grid[], GridInfo sizes){
    /*
     * Makes the outermost ring of cells non-porous solids, by counteracting
     * neighbouring flows.
     */
        int final_y = sizes.col_size-1;
        int final_x = sizes.row_size-1;
        // Deal with Top and Bottom Edges
        if(bm == BoundaryMode::Vertical){
            for(int i = 1; i < final_x; i++) {
                grid[sizes.indx(i,0)] = -grid[sizes.indx(i, 1)];
                grid[sizes.indx(i,final_y)] = -grid[sizes.indx(i, final_y-1)];
            }
        } else{
            for(int i = 1; i < final_x; i++) {
                grid[sizes.indx(i,0)] = grid[sizes.indx(i, 1)];
                grid[sizes.indx(i,final_y)] = grid[sizes.indx(i, final_y-1)];
            }
        }

        // Deal with Left and Right Edges
        if(bm == BoundaryMode::Horizontal){
            for(int j = 1; j < final_y; j++) {
                grid[sizes.indx(0,j)] = -grid[sizes.indx(1,j)];
                grid[sizes.indx(final_x,j)] = -grid[sizes.indx(final_x-1, j)];
            }
        } else{
            for(int j = 1; j < final_y; j++) {
                grid[sizes.indx(0,j)] = grid[sizes.indx(1,j)];
                grid[sizes.indx(final_x,j)] = grid[sizes.indx(final_x-1,j)];
            }
        }

        // Deal with corners explicitly
        grid[sizes.indx(0,0)] = 0.33f * (
            grid[sizes.indx(1,0)] +
            grid[sizes.indx(0,1)] +
            grid[sizes.indx(0,0)]
        );
        grid[sizes.indx(0,final_y)] = 0.33f * (
            grid[sizes.indx(1,final_y)] +
            grid[sizes.indx(0, final_y-1)] +
            grid[sizes.indx(0, final_y)]
        );
        grid[sizes.indx(final_x,0)] = 0.33f * (
            grid[sizes.indx(final_x-1, 0)] +
            grid[sizes.indx(final_x, 1)] +
            grid[sizes.indx(final_x, 0)]
        );
        grid[sizes.indx(final_x,final_y)] = 0.33f * (
            grid[sizes.indx(final_x-1, final_y)] +
            grid[sizes.indx(final_x, final_y-1)]+
            grid[sizes.indx(final_x, final_y)]
        );
    }

    void linear_solve(BoundaryMode bm, float grid[], const float grid_0[], GridInfo sizes, float a, float c, int itters){
    /*
     * Iteratively solve set of linear equations.
     */
        float c_reciprical = 1.f / c;
        for (int k = 0; k < itters; k++) {
            for (int j = 1; j < sizes.col_size - 1; j++) {
                for (int i = 1; i < sizes.row_size - 1; i++) {
                    int index = sizes.indx(i,j);
                    float neighbourhood = (
                        grid[sizes.indx(i+1,j)] + grid[sizes.indx(i-1,j)] +
                        grid[sizes.indx(i,j+1)] + grid[sizes.indx(i,j-1)] +
                        grid[index] + grid[index] // Not sure if these are needed
                    );
                    grid[index] = (grid_0[index] + a * neighbourhood) * c_reciprical;
                }
            }
            enforce_boundaries(bm, grid, sizes);
        }
    }
}