//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_UTILS_H
#define CFD_PHYSICS_UTILS_H
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

int map_to_range(int i_start, int i_end, int o_start, int o_end, int value);
float map_to_range(float i_start, float i_end, float o_start, float o_end, float value);
sf::Color hsv(float hue, float saturation, float value, float alpha);

class GridInfo{
    public:
        int row_size;
        int col_size;
        int grid_size;

        int indx(int x, int y) const;
};
#endif //CFD_PHYSICS_UTILS_H
