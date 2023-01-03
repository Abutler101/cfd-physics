//
// Created by Alexis on 31/12/2022.
//
#include <cmath>
#include "headers/utils.hpp"
int map_to_range(int i_start, int i_end, int o_start, int o_end, int value){
    int gradient = (o_end - o_start) / (i_end - i_start);
    return  o_start + gradient * (value - i_start);
}

float map_to_range(float i_start, float i_end, float o_start, float o_end, float value){
    float gradient = (o_end - o_start) / (i_end - i_start);
    return  o_start + gradient * (value - i_start);
}

sf::Color hsv(float hue, float saturation, float value, float alpha){
    int hue_ = static_cast<int>(hue);
    hue_ %= 360;
    if(hue_==0){hue_=360;}
    if(saturation<0.f){saturation=0.f;}
    if(saturation>1.f){saturation=1.f;}
    if(value<0.f){value=0.f;}
    if(value>1.f){value=1.f;}

    int h=hue_/60;
    float intermediate = float(hue_)/60-h;
    float a = value * (1 - saturation);
    float b = value * (1 - saturation * intermediate);
    float c = value * (1 - saturation * (1 - intermediate));

    switch (h) {
        default:
        case 0: return sf::Color();
        case 1: return sf::Color(b * 255, value * 255, a * 255, alpha);
        case 2: return sf::Color(a * 255, value * 255, c * 255, alpha);
        case 3: return sf::Color(a * 255, b * 255, value * 255, alpha);
        case 4: return sf::Color(c * 255, a * 255, value * 255, alpha);
        case 5: return sf::Color(value*255, a * 255, b * 255, alpha);
        case 6: return sf::Color(value*255, c * 255, a * 255, alpha);
    }
}

int GridInfo::indx(int x, int y) const{
    if(x<0){x=0;}
    else if(x>this->row_size){x=this->row_size;}
    if(y<0){y=0;}
    else if(y>this->col_size){y=this->col_size;}

    return (y*row_size) + x;
}