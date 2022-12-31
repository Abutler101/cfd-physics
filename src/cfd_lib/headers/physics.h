//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_PHYSICS_H
#define CFD_PHYSICS_PHYSICS_H

#include <cstdint>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "utils.hpp"

namespace physics {
    enum BoundaryMode{
        Density, Horizontal, Vertical
    };

    void diffuse(BoundaryMode bm, float *grid[], float *previous_grid[], GridInfo sizes, float dampening, float dt, int itters);

    void project(float *v_x[], float *v_y[], float *prev[], float *divisor[], GridInfo sizes, int itters);

    void advect(BoundaryMode bm, float *grid[], float *prev_grid[], float *veloc_x[], float *veloc_y[], GridInfo sizes, float dt);

    void enforce_boundaries(BoundaryMode bm, float grid[], GridInfo sizes);

    void linear_solve(BoundaryMode bm, float grid[], float grid_0[], GridInfo sizes, float a, float c, int itters);
}

#endif //CFD_PHYSICS_PHYSICS_H
