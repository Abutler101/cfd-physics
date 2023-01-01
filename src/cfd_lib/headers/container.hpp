//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_CONTAINER_HPP
#define CFD_PHYSICS_CONTAINER_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "options.hpp"
#include "utils.hpp"

class Container{
    private:
        uint16_t width_raw;
        uint16_t height_raw;
        uint16_t x_cell_count;
        uint16_t y_cell_count;
        uint32_t total_cells;
        uint16_t cell_size;

        float diffusion;
        float viscosity;

        float *density_grid;
        float *prev_density_grid;
        float *v_x_grid;
        float *v_y_grid;
        float *prev_v_x_grid;
        float *prev_v_y_grid;

    public:
        Container(sf::Vector2<uint16_t> dimensions, uint64_t cell_count, float diff, float visc);
        ~Container();

        void render(sf::RenderWindow *window, RenderOptions *options);
        void step(float dt);
        int pos_to_cell_index(sf::Vector2i pos) const;
        void add_density(sf::Vector2i pos, float amount);
        void add_velocity(sf::Vector2i pos, sf::Vector2f velocity);
        void fade_density();
        [[nodiscard]] GridInfo size_info() const;
};

#endif //CFD_PHYSICS_CONTAINER_HPP
