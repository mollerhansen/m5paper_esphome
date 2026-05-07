// Pikachu Sprites til M5 Paper (ESP32)
// Format: 4-bit Grayscale (16 gråtoner)
// Størrelse: 96x96 pixels (optimeret til 1/10 af bunden af M5 Paper skærmen)

#ifndef PIKACHU_SPRITES_H
#define PIKACHU_SPRITES_H

#include <stdint.h>

// Bredde og højde
const int PIKA_WIDTH = 96;
const int PIKA_HEIGHT = 96;

// 1. Excited
const uint8_t pika_excited[4608] = {
    // Indsæt HEX data fra image2cpp her (4-bit grayscale)
    // Eksempel: 0xFF, 0xEE, 0xDD ...
};

// 2. Glad (Én hale)
const uint8_t pika_glad[4608] = {
    // Indsæt HEX data her
};

// 3. Informerende (Pegefinger oppe, INGEN lyspære)
const uint8_t pika_informing[4608] = {
    // Indsæt HEX data her
};

// 4. Bekymret (Worried)
const uint8_t pika_worried[4608] = {
    // Indsæt HEX data her
};

// 5. Træt (Tired)
const uint8_t pika_tired[4608] = {
    // Indsæt HEX data her
};

// 6. Sur (Angry)
const uint8_t pika_angry[4608] = {
    // Indsæt HEX data her
};

// 7. Sover (Sleeping)
const uint8_t pika_sleeping[4608] = {
    // Indsæt HEX data her
};

#endif
