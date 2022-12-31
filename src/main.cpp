/*
 *
 */
#include <iostream>
#include <cstring>
#include <deque>
#include <tuple>
#include <numeric>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "cfd_lib/headers/container.hpp"
#include "cfd_lib/headers/options.hpp"

// Graphics Settings
const uint16_t Width = 800u;
const uint16_t Height = 800u;
const int FrameRate = 15;
const int FrameAverage = 500;

int main() {
//---------------------------------------------------------
// Window Setup
    auto window = sf::RenderWindow{{Width, Height}, "3D Physics In 2D", sf::Style::Close};
    window.setFramerateLimit(FrameRate);
    uint32_t frame_count = 0;
    std::deque<int32_t> frame_times;
    sf::Clock frame_timer;
    sf::Vector2i current_mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2i previous_mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2i mouse_delta = current_mouse_pos-previous_mouse_pos;
    auto *options = new RenderOptions(true);
    auto *simulation_container = new Container({Width, Height}, 6400, 0.2f, 0.00001f);
//---------------------------------------------------------
// Draw Loop
    while(window.isOpen()){
        frame_timer.restart();
        // Window Events
        for(auto event = sf::Event{}; window.pollEvent(event);){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        simulation_container->add_density(current_mouse_pos, 50);
                    }
                    break;
                case sf::Event::MouseMoved:
                    current_mouse_pos = {event.mouseMove.x, event.mouseMove.y};
                    mouse_delta = current_mouse_pos-previous_mouse_pos;
                    if(mouse_delta.x > 0 or mouse_delta.y > 0){
                        simulation_container->add_velocity(
                            previous_mouse_pos,
                            {static_cast<float>(mouse_delta.x), static_cast<float>(mouse_delta.y)}
                        );
                    }
                    previous_mouse_pos = current_mouse_pos;
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Key::G:
                            options->toggle_draw_grid();
                            break;
                        case sf::Keyboard::Key::C:
                            options->cycle_color_mode();
                            break;
                    }
                    break;
            }
        }

        simulation_container->step(1);
        window.clear();
        simulation_container->render(&window, options);
        window.display();

        // Frame Time Tracking
        frame_count ++;
        int32_t frame_duration = frame_timer.getElapsedTime().asMilliseconds();
        frame_times.emplace_front(frame_duration);
        if(frame_count % FrameAverage == 0){
            frame_times.pop_back();
            auto count = static_cast<float>(frame_times.size());
            auto avg_duration =  std::reduce(frame_times.begin(), frame_times.end()) / count;
            printf("Avg %f ms/frame over last %d frames\n", avg_duration, FrameAverage);
            frame_count = 0;
        }
    }

    delete simulation_container;
    delete options;
    return 0;
}
