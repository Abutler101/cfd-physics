//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_CONTAINER_HPP
#define CFD_PHYSICS_CONTAINER_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Container{
    private:
        uint16_t width_raw;
        uint16_t height_raw;
        uint16_t x_cell_count;
        uint16_t y_cell_count;
        float cell_size;

        float diffusion;
        float viscosity;

        float *density_grid;
        sf::Vector2f *velocity_grid;
        sf::Vector2f *prev_velocity_grid;

    public:
        Container(sf::Vector2<uint16_t> dimensions, uint64_t cell_count);

        void render();
        void step(float dt);
        void add_density(sf::Vector2f pos, float amount);
        void add_velocity(sf::Vector2f pos, sf::Vector2f velocity);
};

#endif //CFD_PHYSICS_CONTAINER_HPP
