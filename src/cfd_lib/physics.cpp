//
// Created by Alexis on 31/12/2022.
//
#include "headers/physics.h"

namespace physics{
    void diffuse(BoundaryMode bm, float *grid[], float *previous_grid[], uint32_t size, float dampening, float dt, int itters){
    /*
     * Diffuses the given value grid with the logic of flowing from
     * high to low
     */
        //...
    }

    void project(float *v_x[], float *v_y[], float *prev[], float *divisor[], uint32_t size, int itters){
    /*
     * Balances velocities such that the fluid remains incompressible &
     * density is neither created nor destroyed by the solver
     */
        //...

    }

    void advect(BoundaryMode bm, float *grid[], float *prev_grid[], float *veloc_x[], float *veloc_y[], uint32_t size, float dt){
    /*
     * Distributes the given value grid based on the given velocity grid
     */
        //...
    }

    void enforce_boundaries(){
    /*
     * Makes the outermost ring of cells non-porous solids, by counteracting
     * neighbouring flows.
     */
        //...
    }

    void linear_solve(){
    /*
     * Iteratively solve set of linear equations.
     */
        //...
    }
}