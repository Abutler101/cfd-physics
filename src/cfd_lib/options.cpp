//
// Created by Alex on 31/12/2022.
//
#include <stdio.h>
#include "headers/options.hpp"
RenderOptions::RenderOptions(bool debug_grid) {
    this->draw_grid=debug_grid;
    this->color_mode=ColorMode::Default;
}

bool RenderOptions::get_draw_grid() const {return this->draw_grid;}
void RenderOptions::toggle_draw_grid() {this->draw_grid=!this->draw_grid;}

ColorMode RenderOptions::get_color_mode() const {return this->color_mode;}
void RenderOptions::cycle_color_mode() {
    this->color_mode=ColorMode((this->color_mode + 1) % 3);
}
