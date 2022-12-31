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
#include "cfd_lib/headers/test.h"

// Graphics Settings
const uint16_t Width = 1500u;
const uint16_t Height = 900u;
const int FrameRate = 500;
const int FrameAverage = 500;

int main() {
//---------------------------------------------------------
// Window Setup
    auto window = sf::RenderWindow{{Width, Height}, "3D Physics In 2D"};
    window.setFramerateLimit(FrameRate);
    uint32_t frame_count = 0;
    std::deque<int32_t> frame_times;
    sf::Clock frame_timer;
    printf("%f\n", goop());
    Test *asd = new Test();
    printf("%d\n\n", asd->sum());
//---------------------------------------------------------
// Draw Loop
    while(window.isOpen()){
        frame_timer.restart();
        // Window Events
        for(auto event = sf::Event{}; window.pollEvent(event);){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        // ...
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
        }
    }
    return 0;
}
