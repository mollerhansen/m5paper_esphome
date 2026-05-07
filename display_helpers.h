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

void draw_alert_zone(display::Display &it, const char* icon, const char* message, display::BaseFont *font_emoji, display::BaseFont *font_text) {
    // Alert Zone is bottom 1/3 (from y=640 to 960)
    // Draw Pikachu placeholder (bottom left)
    it.filled_rectangle(10, 750, 150, 200, COLOR_ON); // Placeholder for Pikachu
    it.print(85, 850, font_text, COLOR_OFF, display::TextAlign::CENTER, "Pika!");

    // Speech bubble
    it.filled_rectangle(170, 650, 360, 280, COLOR_ON);
    it.filled_rectangle(175, 655, 350, 270, COLOR_OFF);
    
    // Bubble triangle (tail)
    it.line(170, 850, 140, 870, COLOR_ON);
    it.line(170, 870, 140, 870, COLOR_ON);

    it.print(350, 670, font_emoji, COLOR_ON, display::TextAlign::TOP_CENTER, icon);
    it.print(350, 750, font_text, COLOR_ON, display::TextAlign::TOP_CENTER, message);
}

void draw_parked_alert(display::Display &it, int x, int y, const char* icon, display::BaseFont *font_emoji) {
    it.print(x, y, font_emoji, COLOR_ON, display::TextAlign::TOP_LEFT, icon);
}
