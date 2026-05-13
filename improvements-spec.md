# M5Paper ESPHome Improvement Specifications

This document outlines the identified issues and proposed architectural/functional improvements for the M5Paper ESPHome project.

## 1. Identified Issues & Bugs

### 1.1 Godnat status (FIXED)
- **Status**: Fixed in `m5paper.yaml` and `display_helpers.h`.
- **Change**: Shortened "Alt er Slukket. Godnat." to "Godnat" and added timestamp in parentheses.

### 1.2 Godnat Lys styring kun på 1. sal (FIXED)
- **Status**: Fixed in `home_assistant_config/scripts.md`.
- **Change**: Limited `light.turn_off` in `house_power_down` script to areas: `stue`, `kokken`, and `bad_stue`.

### 1.3 Kalenderen for idag viser igår (FIXED)
- **Status**: Fixed in `home_assistant_config/update_cal.yaml`.
- **Change**: Explicitly defined start/end times for today's events and added filtering to only show upcoming/ongoing events. Used safer template access to ensure the text is updated/cleared even when no events are found.

## 2. Improvements

### 2.1 Timeouts too long (FIXED)
- **Status**: Fixed in `m5paper.yaml`.
- **Change**: Reduced `power_down_timeout` and `weather_forecast_timeout` from several minutes to 30s.

### 2.2 Taleboble tekster for lange (FIXED)
- **Status**: Fixed in `display_helpers.h`.
- **Change**: Implemented automatic line splitting for messages longer than 20 characters in `draw_alert_zone`.

### 2.3 Sort streg i højre side den sure pikachu (FIXED)
Der er en sort streg langs højrekanten af den sure pikachu.
- **Status**: Fixed in `helper_assistant/pikachu_angry.h`.
- **Change**: Replaced trailing black pixels (0x0000) at the end of the image data array with white pixels (0xffff).

### 3. Etage Rum styring (FIXED)
Stuen er en etage som består af Køkken, bad og stue. 1. sal består Af Georgs værelse, Eskes værelse, Soveværelse og Badeværelse.

### 3.1 Tilføje varme styring i rum (FIXED)
- **Status**: Fixed in `m5paper.yaml` and `display_helpers.h`.
- **Change**: Added touch controls for `Stue`, `Køkken`, and `Bad` on the `STUEN` page.
- **UI Refinement**: Enlarged `+` and `-` buttons (130x80) and removed the `->` arrow for a cleaner look.
- **Ventilation**: Added a prominent "🌬 Luft ud" button at the bottom of the screen.
- **Context**: Displayed the current CO2 level next to the Ventilate button to help decide when to air out.
- **Integration**: Requires HA scripts defined in `home_assistant_config/climate_scripts.md`.

### 3.2 Tilføje lys styring i rum (PLANNED)
Vi skal kunne justere lyset i de rum der har smart pøre med en touch kontrol knap (down-arrow, on/off,up-arrow)

### 3.3 Tidsstempler i statusbaren (FIXED)
- **Status**: Fixed in `display_helpers.h`.
- **Change**: Added `strftime` to the header and appended the last update time to the status message.

---

## Proposed Next Steps

1. **Fix Pikachu Artifact (2.3)**: Clean up the last row of `pikachu_angry.h` to remove the black pixels.
2. **Implement Room Control UI (3.1, 3.2)**: 
   - Design a sub-page or overlay for heat/light control.
   - Use `touchscreen` regions to detect +/- and on/off.
   - Use `homeassistant.service` calls to update states in HA.
