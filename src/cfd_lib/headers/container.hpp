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
        int width_raw;
        int height_raw;
        int x_cell_count;
        int y_cell_count;
        int total_cells;
        int cell_size;

        float diffusion;
        float viscosity;

        float *density_grid;
        float *prev_density_grid;
        float *v_x_grid;
        float *v_y_grid;
        float *prev_v_x_grid;
        float *prev_v_y_grid;

    public:
        Container(sf::Vector2<int> dimensions, int cell_count, float diff, float visc);
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
