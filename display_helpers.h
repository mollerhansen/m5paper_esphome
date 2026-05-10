#pragma once

#include "esphome.h"

using namespace esphome;

// Forward declarations for Pikachu sprites
extern const int PIKA_WIDTH_HAPPY;
extern const int PIKA_HEIGHT_HAPPY;
extern const uint16_t pikachu_happy[];

extern const int PIKA_WIDTH_ANGRY;
extern const int PIKA_HEIGHT_ANGRY;
extern const uint16_t pikachu_angry[];

extern const int PIKA_WIDTH_INFO;
extern const int PIKA_HEIGHT_INFO;
extern const uint16_t pikachu_informative[];

extern const int PIKA_WIDTH_SLEEP;
extern const int PIKA_HEIGHT_SLEEP;
extern const uint16_t pikachu_sleep[];

extern const int PIKA_WIDTH_EXCITED;
extern const int PIKA_HEIGHT_EXCITED;
extern const uint16_t pikachu_excited[];

void draw_header(display::Display &it, const std::string &icon, const std::string &message, time::RealTimeClock *ha_time, display::BaseFont *font_emoji, display::BaseFont *font_text) {
    if (!icon.empty() && icon != "unknown") {
        it.print(10, 15, font_emoji, COLOR_ON, display::TextAlign::TOP_LEFT, icon.c_str());
    }
    
    std::string s_text = (!message.empty() && message != "unknown") ? message : "Klar";
    it.print(50, 15, font_text, COLOR_ON, display::TextAlign::TOP_LEFT, s_text.c_str());
    
    it.strftime(530, 15, font_text, COLOR_ON, display::TextAlign::TOP_RIGHT, "%d. %b  %H:%M", ha_time->now());
    it.line(0, 60, 540, 60);
}

void draw_rounded_rect(display::Display &it, int x, int y, int w, int h, int radius, Color color, bool filled) {
    if (filled) {
        it.filled_rectangle(x + radius, y, w - 2 * radius, h, color);
        it.filled_rectangle(x, y + radius, radius, h - 2 * radius, color);
        it.filled_rectangle(x + w - radius, y + radius, radius, h - 2 * radius, color);
        it.filled_circle(x + radius, y + radius, radius, color);
        it.filled_circle(x + w - radius, y + radius, radius, color);
        it.filled_circle(x + radius, y + h - radius, radius, color);
        it.filled_circle(x + w - radius, y + h - radius, radius, color);
    } else {
        it.line(x + radius, y, x + w - radius, y, color);
        it.line(x + radius, y + h, x + w - radius, y + h, color);
        it.line(x, y + radius, x, y + h - radius, color);
        it.line(x + w, y + radius, x + w, y + h - radius, color);
        it.circle(x + radius, y + radius, radius, color);
        it.circle(x + w - radius, y + radius, radius, color);
        it.circle(x + radius, y + h - radius, radius, color);
        it.circle(x + w - radius, y + h - radius, radius, color);
    }
}

void draw_pikachu(display::Display &it, int x, int y, const uint16_t* sprite, int width, int height, bool mirror_x = false) {
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            uint32_t index = (py * width + px);
            uint16_t color_val = sprite[index];
            // Invert grayscale: 0xFFFF (white) -> 0, 0x0000 (black) -> 15
            uint8_t gray = 15 - (color_val / 4369); 
            
            int draw_x = mirror_x ? (x + width - 1 - px) : (x + px);
            it.draw_pixel_at(draw_x, y + py, Color(gray, 0, 0));
        }
    }
}

const uint16_t* select_pikachu(const std::string &icon) {
    if (icon == "🌬") return pikachu_informative;
    if (icon == "🌙") return pikachu_sleep;
    if (icon == "✨") return pikachu_excited;
    if (icon == "☀" || icon == "🛋" || icon == "🏡") return pikachu_happy;
    // Default or alerts
    if (icon == "🔓" || icon == "🔋" || icon == "🏠") return pikachu_angry;
    
    return pikachu_happy;
}

void draw_alert_zone(display::Display &it, const char* icon, const char* message, display::BaseFont *font_emoji, display::BaseFont *font_text, const uint16_t* pika_sprite = nullptr) {
    // If no sprite provided, try to select based on icon
    if (pika_sprite == nullptr) {
        pika_sprite = select_pikachu(icon);
    }

    // Alert Zone is bottom area (from y=640 to 960)
    
    // Speech bubble background
    int bubble_x = 20;
    int bubble_y = 650;
    int bubble_w = 400;
    int bubble_h = 250;
    int radius = 15;
    int border = 3;

    draw_rounded_rect(it, bubble_x, bubble_y, bubble_w, bubble_h, radius, COLOR_ON, true);
    draw_rounded_rect(it, bubble_x + border, bubble_y + border, bubble_w - 2 * border, bubble_h - 2 * border, radius - border, COLOR_OFF, true);

    // Bubble tail (pointing to the right where Pikachu is)
    it.line(bubble_x + bubble_w, bubble_y + 180, bubble_x + bubble_w + 30, bubble_y + 200, COLOR_ON);
    it.line(bubble_x + bubble_w, bubble_y + 210, bubble_x + bubble_w + 30, bubble_y + 200, COLOR_ON);
    it.line(bubble_x + bubble_w, bubble_y + 181, bubble_x + bubble_w, bubble_y + 209, COLOR_OFF);

    // Text inside bubble
    it.print(bubble_x + bubble_w/2, bubble_y + 30, font_emoji, COLOR_ON, display::TextAlign::TOP_CENTER, icon);
    it.print(bubble_x + bubble_w/2, bubble_y + 110, font_text, COLOR_ON, display::TextAlign::TOP_CENTER, message);

    // Draw Pikachu (bottom right)
    draw_pikachu(it, 400, 780, pika_sprite, 96, 120);
}

void draw_parked_alert(display::Display &it, int x, int y, const char* icon, display::BaseFont *font_emoji) {
    it.print(x, y, font_emoji, COLOR_ON, display::TextAlign::TOP_LEFT, icon);
}
