//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_PHYSICS_H
#define CFD_PHYSICS_PHYSICS_H

#include <cstdint>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

namespace physics {
    enum BoundaryMode{
        Density, Horizontal, Vertical
    };

    void diffuse(BoundaryMode bm, float *grid[], float *previous_grid[], uint32_t size, float dampening, float dt, int itters);

    void project(float *v_x[], float *v_y[], float *prev[], float *divisor[], uint32_t size, int itters);

    void advect(BoundaryMode bm, float *grid[], float *prev_grid[], float *veloc_x[], float *veloc_y[], uint32_t size, float dt);

    void enforce_boundaries();

    void linear_solve();
}

#endif //CFD_PHYSICS_PHYSICS_H
