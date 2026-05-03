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

## 2. Hardware Utilization Improvements

### 2.1 Environmental Sensing (SHT3xD)
- **Status**: Currently unconfigured.
- **Proposal**: Add the `sht3xd` platform to `m5paper.yaml` to monitor local temperature and humidity.
- **Config**:
  ```yaml
  sensor:
    - platform: sht3xd
      temperature:
        id: local_temp
        name: "M5Paper Temperature"
      humidity:
        id: local_humidity
        name: "M5Paper Humidity"
      address: 0x44
      update_interval: 60s
  ```

### 2.2 Battery Monitoring
- **Status**: Missing.
- **Proposal**: Implement battery voltage monitoring. The M5Paper uses an ADC on GPIO35 with a voltage divider (typically 1:2) to measure battery levels.
- **Note**: Requires calibration in the `m5paper` custom component or a standard ADC sensor with `multiply: 2.0`.

### 2.3 Power Management & Deep Sleep
- **Status**: Device is always on, leading to poor battery life.
- **Proposal**: 
    1. Sync ESPHome time to BM8563 RTC on boot.
    2. Implement a "Sleep" button or timeout.
    3. Use `bm8563.apply_sleep_duration` and `m5paper.shutdown_main_power` for true low-power states.

## 3. UI/UX Refinement

### 3.1 Touchscreen Integration
- **Proposal**: Re-enable the `gt911` touchscreen. Even if the rocker is the primary nav, touch "hotspots" can be used for:
    - Forcing a display refresh.
    - Toggling power/sleep.
    - Quick-switching to the Main page.

### 3.2 Dynamic Weather Icons
- **Proposal**: Expand the `draw_fc` lambda to support a wider range of Home Assistant weather states (e.g., `exceptional`, `fog`, `windy`) to match the Noto Emoji font capabilities.
