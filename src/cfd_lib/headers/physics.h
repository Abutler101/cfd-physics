//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_PHYSICS_H
#define CFD_PHYSICS_PHYSICS_H

#include <cstdint>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

namespace physics {
    void diffuse(float *grid[], float *previous_grid[], uint32_t size, float dampening, float dt, int itters);
    void diffuse(sf::Vector2f *grid[], sf::Vector2f *previous_grid[], uint32_t size, float dampening, float dt, int itters);

    void project(sf::Vector2f *grid[], sf::Vector2f *secondary_grid[], uint32_t size, int itters);

    void advect(float *grid[], float *previous_grid[], sf::Vector2f *velocity[], uint32_t size, float dt);
    void advect(sf::Vector2f *grid[], sf::Vector2f *previous_grid[], sf::Vector2f *velocity[], uint32_t size, float dt);

    void enforce_boundaries();

    void linear_solve();
}

#endif //CFD_PHYSICS_PHYSICS_H
