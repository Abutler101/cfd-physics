//
// Created by Alexis on 31/12/2022.
//
#include <math.h>
#include "headers/container.hpp"

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
    this->velocity_grid = new sf::Vector2f[this->total_cells];
    this->prev_velocity_grid = new sf::Vector2f[this->total_cells];
};

Container::~Container() {
    delete this->density_grid;
    delete this->velocity_grid;
    delete this->prev_velocity_grid;
}
//
int Container::pos_to_cell_index(sf::Vector2i pos){
    int coll = floor(static_cast<float>(pos.x) / this->cell_size);
    int row = floor(static_cast<float>(pos.y) / this->cell_size);
    // Deal with any overhang
    if(coll >= this->x_cell_count){coll-=1;}
    if(row >= this->y_cell_count){row-=1;}
    int index = (row * this->x_cell_count) + coll;
    printf("RawPos: (%d, %d) -> CellRef: (%d, %d) -> indx: %d\n", pos.x, pos.y, coll, row, index);
    return index;
}

void Container::render(sf::RenderWindow *window) {
    float casted_size = static_cast<float>(this->cell_size);
    for (int i = 0; i < this->x_cell_count; ++i) {
        for (int j = 0; j < this->y_cell_count; ++j) {
            auto cell_shape = sf::RectangleShape({casted_size, casted_size});
            cell_shape.setFillColor(sf::Color::Transparent);
            cell_shape.setOutlineColor(sf::Color(255, 255, 255, 128));
            cell_shape.setOutlineThickness(1);
            cell_shape.setPosition({i*casted_size, j*casted_size});
            window->draw(cell_shape);
        }
    }
}

void Container::step(float dt) {

}

void Container::add_density(sf::Vector2i pos, float amount) {
    int target_cell = this->pos_to_cell_index(pos);
}

void Container::add_velocity(sf::Vector2i pos, sf::Vector2f velocity) {

}