//
// Created by Alexis on 31/12/2022.
//
#include <math.h>
#include <cstring>
#include "headers/container.hpp"
#include "utils.h"
#include "physics.h"

Container::Container(sf::Vector2<uint16_t> dimensions, uint64_t cell_count, float diff, float visc) {
    // Container is a grid of square cells:
    // higher cell count -> smaller cells-> higher resolution simulation
    // likely won't create cell_count number of cells due to geometric limits
    this->width_raw = dimensions.x;
    this->height_raw = dimensions.y;
    uint64_t area = this->width_raw * this->height_raw;
    float cell_area = static_cast<float>(area) / static_cast<float>(cell_count);

    this->cell_size = floor(pow(cell_area, 0.5f));
    this->x_cell_count = floor(this->width_raw / this->cell_size);
    this->y_cell_count = floor(this->width_raw / this->cell_size);
    this->total_cells = x_cell_count * y_cell_count;
    printf("Container Created with %d cells\n", this->total_cells);

    this->diffusion=diff;
    this->viscosity=visc;

    //1D arrays store 2D grids row by row left -> right
    this->density_grid = new float[this->total_cells];
    this->prev_density_grid = new float[this->total_cells];
    this->v_x_grid = new float[this->total_cells];
    this->v_y_grid = new float[this->total_cells];
    this->prev_v_x_grid = new float[this->total_cells];
    this->prev_v_y_grid = new float[this->total_cells];

    memset(this->density_grid, 0, sizeof(float)*this->total_cells);
    memset(this->prev_density_grid, 0, sizeof(float)*this->total_cells);
    memset(this->v_x_grid, 0, sizeof(float)*this->total_cells);
    memset(this->v_y_grid, 0, sizeof(float)*this->total_cells);
    memset(this->prev_v_x_grid, 0, sizeof(float)*this->total_cells);
    memset(this->prev_v_y_grid, 0, sizeof(float)*this->total_cells);

};

Container::~Container() {
    delete this->density_grid;
    delete this->v_x_grid;
    delete this->v_y_grid;
    delete this->prev_v_x_grid;
    delete this->prev_v_y_grid;
}

int Container::pos_to_cell_index(sf::Vector2i pos) const{
    int coll = floor(static_cast<float>(pos.x) / this->cell_size);
    int row = floor(static_cast<float>(pos.y) / this->cell_size);
    // Deal with any overhang
    if(coll >= this->x_cell_count){coll-=1;}
    if(row >= this->y_cell_count){row-=1;}
    int index = (row * this->x_cell_count) + coll;
    //printf("RawPos: (%d, %d) -> CellRef: (%d, %d) -> indx: %d\n", pos.x, pos.y, coll, row, index);
    return index;
}

void Container::render(sf::RenderWindow *window, RenderOptions *options) {
    float casted_size = static_cast<float>(this->cell_size);
    for (int i = 0; i < this->x_cell_count; ++i) {
        for (int j = 0; j < this->y_cell_count; ++j) {
            int cell_index = (j * this->x_cell_count) + i;
            auto cell_shape = sf::RectangleShape({casted_size, casted_size});
            uint8_t mapped_density;
            if(density_grid[cell_index] > 255){mapped_density=255;}
            else{mapped_density=floor(density_grid[cell_index]);}
            sf::Color cell_color = sf::Color();
            switch (options->get_color_mode()) {
                case ColorMode::Default:
                    cell_color = sf::Color(255, 255, 255, mapped_density);
                    cell_shape.setFillColor(cell_color);
                    break;
                case ColorMode::Velocity:
                    cell_color.r = map_to_range(-5.f,5.f, 0.f, 255.f, this->v_x_grid[cell_index]);
                    cell_color.g = map_to_range(-5.f,5.f, 0.f, 255.f, this->v_y_grid[cell_index]);
                    cell_color.b = 255;
                    cell_shape.setFillColor(cell_color);
                    break;
                case ColorMode::Hsb:
                    cell_color = hsv(density_grid[cell_index], 1, 1, 255);
                    cell_shape.setFillColor(cell_color);
                    break;
            }
            if(options->get_draw_grid()){
                cell_shape.setOutlineColor(sf::Color(0, 255, 0, 191));
                cell_shape.setOutlineThickness(1);
            }
            cell_shape.setPosition({i*casted_size, j*casted_size});
            window->draw(cell_shape);
        }
    }
}

void Container::step(float dt) {
    int ITTER_COUNT = 8;
    physics::diffuse(
        physics::BoundaryMode::Horizontal,
        &this->v_x_grid,
        &this->prev_v_x_grid,
        this->total_cells,
        this->viscosity,
        dt,
        ITTER_COUNT
    );
    physics::diffuse(
            physics::BoundaryMode::Vertical,
            &this->v_y_grid,
            &this->prev_v_y_grid,
            this->total_cells,
            this->viscosity,
            dt,
            ITTER_COUNT
    );

    physics::project(
        &this->prev_v_x_grid,
        &this->prev_v_y_grid,
        &this->v_x_grid,
        &this->v_y_grid,
        this->total_cells,
        ITTER_COUNT
    );

    physics::advect(
        physics::BoundaryMode::Horizontal,
        &this->v_x_grid,
        &this->prev_v_x_grid,
        &this->prev_v_x_grid,
        &this->prev_v_y_grid,
        this->total_cells,
        dt
    );
    physics::advect(
        physics::BoundaryMode::Vertical,
        &this->v_y_grid,
        &this->prev_v_y_grid,
        &this->prev_v_x_grid,
        &this->prev_v_y_grid,
        this->total_cells,
        dt
    );

    physics::project(
            &this->prev_v_x_grid,
            &this->prev_v_y_grid,
            &this->v_x_grid,
            &this->v_y_grid,
            this->total_cells,
            ITTER_COUNT
    );

    physics::diffuse(
        physics::BoundaryMode::Density,
        &this->prev_density_grid,
        &this->density_grid,
        this->total_cells,
        this->diffusion,
        dt,
        ITTER_COUNT
    );
    physics::advect(
            physics::BoundaryMode::Density,
            &this->density_grid,
            &this->prev_density_grid,
            &this->v_x_grid,
            &this->v_y_grid,
            this->total_cells,
            dt
    );
}

void Container::add_density(sf::Vector2i pos, float amount) {
    int target_cell = this->pos_to_cell_index(pos);
    this->density_grid[target_cell] += amount;
}

void Container::add_velocity(sf::Vector2i pos, sf::Vector2f velocity) {
    int start_cell = this->pos_to_cell_index(pos);
    this->v_x_grid[start_cell] += velocity.x;
    this->v_y_grid[start_cell] += velocity.y;
}