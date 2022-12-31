//
// Created by Alex on 31/12/2022.
//

#ifndef CFD_PHYSICS_OPTIONS_HPP
#define CFD_PHYSICS_OPTIONS_HPP

enum ColorMode{
    Default, Hsb, Velocity
};

class RenderOptions{
    private:
        bool draw_grid;
        ColorMode color_mode;
    public:
        RenderOptions(bool debug_grid);

        bool get_draw_grid() const;
        void toggle_draw_grid();

        ColorMode get_color_mode() const;
        void cycle_color_mode();
};

#endif //CFD_PHYSICS_OPTIONS_HPP
