//
// Created by Alexis on 31/12/2022.
//
#include <cmath>
#include "headers/physics.h"
#include "utils.hpp"

namespace physics{
    void diffuse(BoundaryMode bm, float grid[], float previous_grid[], GridInfo sizes, float dampening, float dt, int itters){
    /*
     * Diffuses the given value grid with the logic of flowing from
     * high to low
     */
        float a = dt * dampening * (sizes.row_size - 2) * (sizes.col_size - 2);
        float c = 1 + (6 * a);
        linear_solve(bm, grid, previous_grid, sizes, a, c, itters);
    }

    void project(float v_x[], float v_y[], float prev[], float divisor[], GridInfo sizes, int itters){
    /*
     * Balances velocities such that the fluid remains incompressible &
     * density is neither created nor destroyed by the solver
     */
        int final_y = sizes.col_size-1;
        int final_x = sizes.row_size-1;
        int index;

        for (int j = 1; j < final_y; j++) {
            for (int i = 1; i < final_x; i++) {
                index = sizes.indx(i, j);
                float neighbours = (
                    v_x[sizes.indx(i+1, j)] - v_x[sizes.indx(i-1, j)] +
                    v_y[sizes.indx(i, j+1)] - v_y[sizes.indx(i, j-1)]
                );
                divisor[index] = -0.5f * neighbours / sizes.col_size;
                prev[index] = 0;
            }
        }

        enforce_boundaries(BoundaryMode::Density, divisor, sizes);
        enforce_boundaries(BoundaryMode::Density, prev, sizes);
        linear_solve(BoundaryMode::Density, prev, divisor, sizes, 1, 6, itters);

        for (int j = 1; j < final_y; j++) {
            for (int i = 1; i < final_x; i++) {
                index = sizes.indx(i, j);
                v_x[index] -= 0.5f * (prev[sizes.indx(i+1, j)] - prev[sizes.indx(i-1, j)]) * sizes.row_size;
                v_y[index] -= 0.5f * (prev[sizes.indx(i, j+1)] - prev[sizes.indx(i, j-1)]) * sizes.col_size;
            }
        }
        enforce_boundaries(BoundaryMode::Horizontal, v_x, sizes);
        enforce_boundaries(BoundaryMode::Vertical, v_y, sizes);
    }

    void advect(BoundaryMode bm, float grid[], float prev_grid[], float veloc_x[], float veloc_y[], GridInfo sizes, float dt){
    /*
     * Distributes the given value grid based on the given velocity grid
     */


        // float casts of size vars
        auto row_size_f = static_cast<float>(sizes.row_size);
        auto col_size_f = static_cast<float>(sizes.col_size);
        // how far to look in time for each axis
        float dt_x = dt * row_size_f;
        float dt_y = dt * col_size_f;
        // index shortcuts
        int last_y = sizes.col_size-1;
        int last_x = sizes.row_size-1;
        int index;

        // intermediate variables
        float i0, i1, j0, j1;
        float s0, s1, t0, t1;
        float dist_x, dist_y, x, y;

        for(int j = 1; j < last_y; j++) {
            for(int i = 1; i < last_x; i++) {
                index=sizes.indx(i,j);
                dist_x = dt_x * veloc_x[index];
                dist_y = dt_y * veloc_y[index];
                x = static_cast<float>(i) - dist_x;
                y = static_cast<float>(j) - dist_y;

                if(x < 0.5f){x = 0.5f;}
                if(x > row_size_f + 0.5f){x = row_size_f + 0.5f;}
                i0 = floorf(x);
                i1 = i0 + 1.0f;

                if(y < 0.5f){y = 0.5f;}
                if(y > col_size_f + 0.5f){y = col_size_f + 0.5f;}
                j0 = floorf(y);
                j1 = j0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;

                int i0i = i0;
                int i1i = i1;
                int j0i = j0;
                int j1i = j1;

                grid[index] =
                        s0 * (t0 * prev_grid[sizes.indx(i0i, j0i)] + t1 * prev_grid[sizes.indx(i0i, j1i)]) +
                        s1 * (t0 * prev_grid[sizes.indx(i1i, j0i)] + t1 * prev_grid[sizes.indx(i1i, j1i)]);
            }
        }
        enforce_boundaries(bm, grid, sizes);
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
                        grid[sizes.indx(i,j+1)] + grid[sizes.indx(i,j-1)]
                    );
                    grid[index] = (grid_0[index] + a * neighbourhood) * c_reciprical;
                }
            }
            enforce_boundaries(bm, grid, sizes);
        }
    }
}