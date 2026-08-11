# M5Paper ESPHome Improvement Specifications

This document outlines the identified issues and proposed architectural/functional improvements for the M5Paper ESPHome project.

## 1. Identified Issues & Bugs

### 1.1 vasker hele tiden (DONE)

Jeg tror der er en fejl, som gør at natlåsen den giver vaskealarmen i stedet for Godnat låse alarmen.

**Fix:** 
- Swapped priority in `home_assistant_config/update_status.yaml` so the door lock alarm (Priority 2) takes precedence over the washing machine alert (Priority 3).
- Adjusted washing machine power threshold to `above: 2` and `below: 10` to avoid triggering on standby power (observed at 1.0W).

### 1.2 natlåsens rutine aktiveres men vises ikke længere på skærmen

Jeg ved ikke om det nogle side har været tilfældet men når min natlås rutine køre på timeren kl 22 vises der ikke en alert på skærmen. Er der noget jeg skal opdatere i min rutine i HA?

### 1.3 Calendar is still not updating (DONE)

Both the week view and the day view is not correctly updating. We have previously tried to troubleshoot the gcal integration on Home Assist. 

**Fix:**
- **Fixed Home Assistant State String Limit Overflow**: Home Assistant limits `input_text` state strings to 255 characters max. Long event lists previously exceeded 255 characters, causing HA to abort `input_text.set_value` and block updates. Capped total line length to 245 characters and truncated long event titles.
- **Fixed ISO Datetime Comparison Bug**: Replaced Jinja `selectattr('end', 'greaterthan', now().isoformat())` (which performed string comparison where all-day date strings `"YYYY-MM-DD"` were incorrectly evaluated as smaller than `"YYYY-MM-DDTHH:MM..."` and discarded) with `as_timestamp(event.end) > as_timestamp(now())` epoch timestamp comparison.
- **Fixed All-Day Event Display**: Added formatting logic so all-day events display as `"Hele dagen"` instead of `"00:00"`.
- **Fixed Entity Dictionary Key Fallback**: Updated template to dynamically fetch `(agenda_idag.values() | list | first)` so calendar retrieval does not fail if entity mapping keys differ.
- **Modernized HA Action Syntax**: Replaced deprecated `service:` calls with `action:`.
- **Added Immediate Display Refresh**: Added `on_value` triggers to `cal_today` and `cal_week` in `m5paper.yaml` to trigger immediate e-ink display updates when calendar data updates.

### 1.4 pikachu vejrudsigt viser både sovende og instruerende pikachu

Vejrudsigten skal ikke vise sovende, sovende skal først komme igen når vejrudsigten går væk.

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

### 2.3 Alert når gcal integrationen fejler

Vi har gang på gang problemer med gcal integrationen i HA pga auth issues. Lad Pikachu informere om problemet, så jeg kan fixe det.
