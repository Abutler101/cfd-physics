//
// Created by Alexis on 31/12/2022.
//
#include "headers/physics.h"

namespace physics{
    void diffuse(float *grid[], float *previous_grid[], uint32_t size, float dampening, float dt, int itters){
    /*
     * Diffuses the given value grid with the logic of flowing from
     * high to low
     */
        //...
    }
    void diffuse(sf::Vector2f *grid[], sf::Vector2f *previous_grid[], uint32_t size, float dampening, float dt, int itters){
        /*
         * Diffuses the given value grid with the logic of flowing from
         * high to low
         */
        //...
    }

    void project(sf::Vector2f *grid[], sf::Vector2f *secondary_grid[], uint32_t size, int itters){
    /*
     * Balances grid values such that the fluid remains incompressible &
     * density is neither created nor destroyed by the solver
     */
        //...

    }

    void advect(float *grid[], float *previous_grid[], sf::Vector2f *velocity[], uint32_t size, float dt){
    /*
     * Distributes the given value grid based on the given velocity grid
     */
        //...
    }
    void advect(sf::Vector2f *grid[], sf::Vector2f *previous_grid[], sf::Vector2f *velocity[], uint32_t size, float dt){
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