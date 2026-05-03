#pragma once

#include "esphome.h"

using namespace esphome;

void draw_header(display::Display &it, text_sensor::TextSensor *status_icon, text_sensor::TextSensor *status_text, time::RealTimeClock *ha_time, display::BaseFont *font_emoji, display::BaseFont *font_text) {
    if (status_icon->has_state() && status_icon->state != "unknown") {
        it.print(10, 15, font_emoji, COLOR_ON, display::TextAlign::TOP_LEFT, status_icon->state.c_str());
    }
    
    std::string s_text = (status_text->has_state() && status_text->state != "unknown") ? status_text->state : "Klar";
    it.print(50, 15, font_text, COLOR_ON, display::TextAlign::TOP_LEFT, s_text.c_str());
    
    it.strftime(530, 15, font_text, COLOR_ON, display::TextAlign::TOP_RIGHT, "%d. %b  %H:%M", ha_time->now());
    it.line(0, 60, 540, 60);
}
