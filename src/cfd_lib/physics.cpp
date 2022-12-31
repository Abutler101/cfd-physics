//
// Created by Alexis on 31/12/2022.
//
#include "headers/physics.h"

void diffuse(){
/*
 * Diffuses the given value grid with the logic of trying to minimise
 * Diff between peaks and troughs
 */
    //...
}

void project(){
/*
 * Balances velocities such that the fluid remains incompressible &
 * density is neither created nor destroyed by the solver
 */
    //...

}

void advect(){
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