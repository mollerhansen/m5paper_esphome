# M5Paper ESPHome Improvement Specifications

This document outlines the identified issues and proposed architectural/functional improvements for the M5Paper ESPHome project.

## 1. Identified Issues & Bugs

### 1.1 Calendar Separator Mismatch
- **Issue**: `update_cal.yaml` (Home Assistant) sends calendar events separated by `\n`, but `m5paper.yaml` (ESPHome) attempts to split the string using `|`.
- **Impact**: Calendar events do not render correctly on the display.
- **Fix**: Align both configurations to use `\n` and simplify the ESPHome lambda to handle newlines natively if supported, or fix the splitting logic.

### 1.2 Redundant Display Lambda Code
- **Issue**: The Header (Status icon, text, time, and line divider) is duplicated across all 4 pages in `m5paper.yaml`.
- **Impact**: Harder to maintain; changes to the header must be applied in 4 places.
- **Fix**: Move shared drawing logic into a C++ header file (`display_helpers.h`) and call it from the YAML lambdas.
- **Status**: **Completed**. Logic moved to `draw_header` in `display_helpers.h`.

## 2. Hardware Utilization Improvements

### 2.1 Environmental Sensing (SHT3xD)
- **Status**: **Completed**. SHT3xD configured and reporting.

### 2.2 Battery Monitoring
- **Status**: **Completed**. ADC sensor implemented on GPIO35 with 2.0 multiplier.

### 2.3 Power Management & Deep Sleep
- **Status**: **Partially Completed**. RTC sync and shutdown actions implemented. Shutdown mapped to rocker center hold and bottom touch edge.

## 3. UI/UX Refinement

### 3.1 Touchscreen Integration
- **Proposal**: Re-enable the `gt911` touchscreen. Even if the rocker is the primary nav, touch "hotspots" can be used for:
    - Forcing a display refresh.
    - Toggling power/sleep.
    - Quick-switching to the Main page.
- **Status**: **Completed**. GT911 integrated with touch zones for refresh, dismiss, and shutdown.

### 3.2 Dynamic Weather Icons
- **Status**: **Completed**. `draw_fc` expanded with comprehensive state mapping.

### 3.3 Pikachu som hjælper
- **Proposal**: Alarm vinduet i bunden skal være en talebobble med Pikachu i forgrunden. Alt efter alarm skal pikachu være glad, bedrevidende, bekymret, træt..
- **Status**: **Completed**. 5 emotions implemented: Happy, Angry, Informative, Sleep, and Excited. Logic in `select_pikachu` handles automatic switching based on status icons. Color inversion fixed.

### 3.4 fjerne alarmvinduet
- **Proposal**: brug touch interfacet til at dismisse alarmvinduet. 
- **Status**: **Completed**. Touching the bottom area (y > 640) dismisses the alert.
### 3.5 easter egg
- **Proposal**: Få pikachu til at dukke frem med forskellige udsagn og udtryk tilfældigt. Evt tilføjer vi easter eggs i update yaml. De skal også dukke frem og frosvinde ved tryk i bunden af skærmen. 

## 4. Flere Ideer

### 4.1 fler-dags prognose 
- **Proposal**: Vis 5 dags prognose i ugekalenderen

### 4.2 Device batterier 

- **Proposal**: Vi det batterier der er løbet tør. Måske lave en hel side under kalender siden med batteri statuser
