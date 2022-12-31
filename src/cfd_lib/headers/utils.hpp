//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_UTILS_H
#define CFD_PHYSICS_UTILS_H
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

uint8_t map_to_range(uint8_t i_start, uint8_t i_end, uint8_t o_start, uint8_t o_end, uint8_t value);
float map_to_range(float i_start, float i_end, float o_start, float o_end, float value);
sf::Color hsv(float hue, float saturation, float value, float alpha);

class GridInfo{
    public:
        uint16_t row_size;
        uint16_t col_size;
        uint32_t grid_size;

        int indx(int x, int y) const;
};
#endif //CFD_PHYSICS_UTILS_H
