# M5Paper ESPHome Improvement Specifications

This document outlines the identified issues and proposed architectural/functional improvements for the M5Paper ESPHome project.

## 1. Identified Issues & Bugs

### 1.1 vasker hele tiden (DONE)

Jeg tror der er en fejl, som gør at natlåsen den giver vaskealarmen i stedet for Godnat låse alarmen.

**Fix:** 
- Swapped priority in `home_assistant_config/update_status.yaml` so the door lock alarm (Priority 2) takes precedence over the washing machine alert (Priority 3).
- Adjusted washing machine power threshold to `above: 2` and `below: 10` to avoid triggering on standby power (observed at 1.0W).

## 2. Improvements

Stuen er en etage som består af Køkken, bad og stue. 1. sal består Af Georgs værelse, Eskes værelse, Soveværelse og Badeværelse.

### 2.1 Tilføje lys styring i rum (PLANNED)
Vi skal kunne justere lyset i de rum der har smart pøre med en touch kontrol knap (down-arrow, on/off,up-arrow). Vi skal finde ud af at skifte mellem lys og temperatur styrings kontrollen. Måske ved en lys/radiator ikon switch i toppen af etage panelet.

### 2.2 Pikachu sover når der intet sker (DONE)

Lad os lade pikachu ligge og sove i bunden af skærmen på midten når der ikke sker noget. 

**Fix:**
- Added `draw_sleeping_pikachu` function to `display_helpers.h`.
- Integrated sleeping Pikachu on all pages when no alerts or power-down requests are active.
- Adjusted "Luft ud" button and CO2 display on the living room page to avoid overlap with the sleeping Pikachu.
- Updated touch zones to match the new button layout.
- **Fixed vertical line artifact** in `pikachu_sleep.h` by removing trailing black pixels (0x0000) at the end of sprite rows.


